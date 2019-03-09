/*	$NetBSD: obio.c,v 1.31 1997/10/04 19:46:20 gwr Exp $	*/

/*-
 * Copyright (c) 1996 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Adam Glass and Gordon W. Ross.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <machine/autoconf.h>
#include <machine/control.h>
#include <machine/machdep.h>
#include <machine/mon.h>
#include <machine/obio.h>
#include <machine/pte.h>

static int  obio_match __P((struct device *, struct cfdata *, void *));
static void obio_attach __P((struct device *, struct device *, void *));
static int  obio_print __P((void *, const char *parentname));
static int	obio_submatch __P((struct device *, struct cfdata *, void *));

struct cfattach obio_ca = {
	sizeof(struct device), obio_match, obio_attach
};

struct cfdriver obio_cd = {
	NULL, "obio", DV_DULL
};

static int
obio_match(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{
	struct confargs *ca = aux;

	if (ca->ca_bustype != BUS_OBIO)
		return (0);
	return(1);
}

#define	OBIO_INCR	0x020000
#define OBIO_END	0x200000

static void
obio_attach(parent, self, aux)
	struct device *parent;
	struct device *self;
	void *aux;
{
	struct confargs *ca = aux;
	int	addr;

	printf("\n");

	/* Configure these in order of address. */
	for (addr = 0; addr < OBIO_END; addr += OBIO_INCR) {
		/* Our parent set ca->ca_bustype already. */
		ca->ca_paddr = addr;
		/* These are filled-in by obio_submatch. */
		ca->ca_intpri = -1;
		ca->ca_intvec = -1;
		(void) config_found_sm(self, ca, obio_print, obio_submatch);
	}
}

/*
 * Print out the confargs.  The (parent) name is non-NULL
 * when there was no match found by config_found().
 */
static int
obio_print(args, name)
	void *args;
	const char *name;
{

	/* Be quiet about empty OBIO locations. */
	if (name)
		return(QUIET);

	/* Otherwise do the usual. */
	return(bus_print(args, name));
}

int
obio_submatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{
	struct confargs *ca = aux;
	cfmatch_t submatch;

	/*
	 * Note that a defaulted address locator can never match
	 * the value of ca->ca_paddr set by the obio_attach loop.
	 * Without this diagnostic, any device with a defaulted
	 * address locator would always be silently unmatched.
	 * Therefore, just disallow default addresses on OBIO.
	 */
#ifdef	DIAGNOSTIC
	if (cf->cf_paddr == -1)
		panic("obio_submatch: invalid address for: %s%d\n",
			cf->cf_driver->cd_name, cf->cf_unit);
#endif

	/*
	 * Note that obio_attach calls config_found_sm() with
	 * this function as the "submatch" and ca->ca_paddr
	 * set to each of the possible OBIO locations, so we
	 * want to reject any unmatched address here.
	 */
	if (cf->cf_paddr != ca->ca_paddr)
		return 0;

	/*
	 * Copy the locators into our confargs for the child.
	 * Note: ca->ca_bustype was set by our parent driver
	 * (mainbus) and ca->ca_paddr was set by obio_attach.
	 */
	ca->ca_intpri = cf->cf_intpri;
	ca->ca_intvec = -1;

	/* Now call the match function of the potential child. */
	submatch = cf->cf_attach->ca_match;
	if (submatch == NULL)
		panic("obio_submatch: no match function for: %s\n",
			  cf->cf_driver->cd_name);

	return ((*submatch)(parent, cf, aux));
}


/*****************************************************************/

/*
 * Spacing of "interesting" OBIO mappings.  We will
 * record only those with an OBIO address that is a
 * multiple of SAVE_INCR and below SAVE_LAST.
 * The saved mappings are just one page each, which
 * is good enough for all the devices that use this.
 */
#define SAVE_SHIFT 17
#define SAVE_INCR (1<<SAVE_SHIFT)
#define SAVE_MASK (SAVE_INCR-1)
#define SAVE_SLOTS  16
#define SAVE_LAST (SAVE_SLOTS * SAVE_INCR)

/*
 * This is our record of "interesting" OBIO mappings that
 * the PROM has left in the virtual space reserved for it.
 * Each non-null array element holds the virtual address
 * of an OBIO mapping where the OBIO address mapped is:
 *     (array_index * SAVE_INCR)
 * and the length of the mapping is one page.
 */
static caddr_t prom_mappings[SAVE_SLOTS];

caddr_t obio_find_mapping(int pa, int size)
{
	if ((size <= NBPG) &&
		(pa < SAVE_LAST) &&
		((pa & SAVE_MASK) == 0))
	{
		return prom_mappings[pa >> SAVE_SHIFT];
	}
	return (caddr_t)0;
}

/*
 * This defines the permission bits to put in our PTEs.
 * Device space is never cached, and the PROM appears to
 * leave off the "no-cache" bit, so we can do the same.
 */
#define PGBITS (PG_VALID|PG_WRITE|PG_SYSTEM)

static void
save_prom_mappings __P((void))
{
	vm_offset_t pa, segva, pgva;
	int pte, sme, i;

	segva = (vm_offset_t)MONSTART;
	while (segva < (vm_offset_t)MONEND) {
		sme = get_segmap(segva);
		if (sme == SEGINV) {
			segva += NBSG;
			continue;			/* next segment */
		}
		/*
		 * We have a valid segmap entry, so examine the
		 * PTEs for all the pages in this segment.
		 */
		pgva = segva;	/* starting page */
		segva += NBSG;	/* ending page (next seg) */
		while (pgva < segva) {
			pte = get_pte(pgva);
			if ((pte & (PG_VALID | PG_TYPE)) ==
				(PG_VALID | PGT_OBIO))
			{
				/* Have a valid OBIO mapping. */
				pa = PG_PA(pte);
				/* Is it one we want to record? */
				if ((pa < SAVE_LAST) &&
					((pa & SAVE_MASK) == 0))
				{
					i = pa >> SAVE_SHIFT;
					if (prom_mappings[i] == NULL) {
						prom_mappings[i] = (caddr_t)pgva;
#ifdef	DEBUG
						mon_printf("obio: found pa=0x%x\n", pa);
#endif
					}
				}
				/* Make sure it has the right permissions. */
				if ((pte & PGBITS) != PGBITS) {
#ifdef	DEBUG
					mon_printf("obio: fixing pte=0x%x\n", pte);
#endif
					pte |= PGBITS;
					set_pte(pgva, pte);
				}
			}
			pgva += NBPG;		/* next page */
		}
	}
}

/*
 * These are all the OBIO address that are required early in
 * the life of the kernel.  All are less than one page long.
 */
static vm_offset_t required_mappings[] = {
	/* Basically the first six OBIO devices. */
	OBIO_ZS_KBD_MS,
	OBIO_ZS_TTY_AB,
	OBIO_EEPROM,
	OBIO_CLOCK,
	OBIO_MEMERR,
	OBIO_INTERREG,
	(vm_offset_t)-1,	/* end marker */
};

static void
make_required_mappings __P((void))
{
	vm_offset_t *rmp;

	rmp = required_mappings;
	while (*rmp != (vm_offset_t)-1) {
		if (!obio_find_mapping(*rmp, NBPG)) {
			/*
			 * XXX - Ack! Need to create one!
			 * I don't think this can happen, but if
			 * it does, we can allocate a PMEG in the
			 * "high segment" and add it there. -gwr
			 */
			mon_printf("obio: no mapping for 0x%x\n", *rmp);
			sunmon_abort();
		}
		rmp++;
	}
}


/*
 * Find mappings for devices that are needed before autoconfiguration.
 * We first look for and record any useful PROM mappings, then call
 * the "init" functions for drivers that we need to use before the
 * normal autoconfiguration calls configure().  Warning: this is
 * called before pmap_bootstrap, so no allocation allowed!
 */
void
obio_init()
{
	save_prom_mappings();
	make_required_mappings();

	/*
	 * Find the interrupt reg mapping and turn off the
	 * interrupts, otherwise the PROM clock interrupt
	 * would poll the zs and toggle some LEDs...
	 */
	intreg_init();

	/* Make the zs driver ready for console duty. */
	zs_init();
}

/*
 * This function is used by some OBIO drivers to conserve
 * kernel virtual space by sharing mappings made by the
 * PROM monitor.  If we could not find any mapping made by
 * the PROM monitor, then make our own as usual.
 */
caddr_t
obio_mapin(obio_addr, obio_size)
	int obio_addr, obio_size;
{
	caddr_t cp;

	cp = obio_find_mapping((vm_offset_t)obio_addr, obio_size);
	if (cp)
		return (cp);

	cp = bus_mapin(BUS_OBIO, obio_addr, obio_size);
	return (cp);
}
