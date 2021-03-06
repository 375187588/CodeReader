//
// smart_proxy_ch.cpp,v 1.15 2001/02/02 02:31:29 fhunleth Exp
//
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    smart_proxy_ch.cpp
//
// = DESCRIPTION
//    This provides code generation for smart proxy classes for an
//    interface in the client header.
//
// = AUTHOR
//    Kirthika Parameswaran  <kirthika@cs.wustl.edu>
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_interface.h"

ACE_RCSID(be_visitor_interface, smart_proxy_ch, "smart_proxy_ch.cpp,v 1.15 2001/02/02 02:31:29 fhunleth Exp")


// ************************************************************
//  smart proxy class in header
// ************************************************************


be_visitor_interface_smart_proxy_ch::be_visitor_interface_smart_proxy_ch
(be_visitor_context *ctx)
  : be_visitor_interface (ctx)
{
}

be_visitor_interface_smart_proxy_ch::~be_visitor_interface_smart_proxy_ch (void)
{
}

int be_visitor_interface_smart_proxy_ch::visit_interface (be_interface *node)
{

  if (be_global->gen_smart_proxies ())
    {

      TAO_OutStream *os = this->ctx_->stream ();

      be_type *bt;

      // set the right type;
      if (this->ctx_->alias ())
        bt = this->ctx_->alias ();
      else
        bt = node;
      // output the class defn

      *os << "class " << be_global->stub_export_macro ()<< " "
          << "TAO_" << node->flat_name ()
          << "_Default_Proxy_Factory" << be_nl
          << "{" << be_nl
          << "public:" << be_idt_nl << be_nl
          << "TAO_" << node->flat_name ()
          << "_Default_Proxy_Factory (int permanent = 1);"
          << be_nl 
          <<"// <permanent> signifies that the proxy factory will remain" <<be_nl 
          <<"// registered with the Proxy Factory Adapter until the program"<<be_nl
          <<"// terminates. That is, it will be a one-shot factory for the "<<be_nl
          <<"// interface.  If this value is set to 0, then the factory will"<<be_nl
          <<"// be unregistered after the first invocation providing the "<<be_nl
          << "// flexibility of having a different smart proxy per object "<<be_nl
          <<"// instead of per interface."<<be_nl<< be_nl
          << "virtual ~TAO_" << node->flat_name ()
          << "_Default_Proxy_Factory (void);" << be_nl << be_nl
          << "virtual "<< node->local_name ()
          << "_ptr create_proxy (" << be_idt << be_idt_nl
          << node->local_name ()
          << "_ptr proxy," << be_nl
          << "CORBA::Environment &ACE_TRY_ENV = " << be_idt_nl
          << "TAO_default_environment ()" << be_uidt << be_uidt_nl
          << ");" << be_uidt << be_uidt_nl
          << "};\n\n";

      *os << "class " << be_global->stub_export_macro ()<< " "
          << "TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter" << be_nl
          << "{" << be_nl
          << "public:" << be_idt_nl << be_nl
          << "friend class TAO_Singleton<TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter, TAO_SYNCH_RECURSIVE_MUTEX>;" << be_nl << be_nl
          << "int register_proxy_factory (" << be_idt << be_idt_nl
          << "TAO_" << node->flat_name () << "_Default_Proxy_Factory *df,"<< be_nl
          << "int one_shot_factory = 1,"<<be_nl
          << "CORBA::Environment &ACE_TRY_ENV = " << be_idt_nl
          << "TAO_default_environment ()" << be_uidt << be_uidt_nl
          << ");" << be_uidt_nl << be_nl
          << "int unregister_proxy_factory (" << be_idt << be_idt_nl
          << "CORBA::Environment &ACE_TRY_ENV = " << be_idt_nl
          << "TAO_default_environment ()" << be_uidt << be_uidt_nl
          << ");" << be_uidt_nl << be_nl
          << node->local_name ()
          << "_ptr create_proxy (" << be_idt << be_idt_nl
          << node->local_name () << "_ptr proxy," << be_nl
          << "CORBA::Environment &ACE_TRY_ENV = " << be_idt_nl
          << "TAO_default_environment ()" << be_uidt << be_uidt_nl
          << ");" << be_uidt << be_uidt_nl << be_nl
          << "protected:" << be_idt_nl
          << "TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter (void);" << be_nl
          << "~TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter (void);" << be_nl
          << "TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter &operator= (" << be_idt << be_idt_nl
          << "const TAO_" << node->flat_name ()
          << "_Proxy_Factory_Adapter &" << be_uidt_nl
          << ");" << be_uidt_nl
          << "TAO_" << node->flat_name ()
          << "_Default_Proxy_Factory *proxy_factory_;" << be_nl
          << "int one_shot_factory_;" << be_nl
          << "int disable_factory_;"<<be_nl
          << "TAO_SYNCH_RECURSIVE_MUTEX lock_;"<<be_nl << be_uidt_nl
          << "};\n\n";

      os->indent ();
      *os << "typedef TAO_Singleton<TAO_"<<node->flat_name ()
          << "_Proxy_Factory_Adapter, TAO_SYNCH_RECURSIVE_MUTEX> TAO_"
          << node->flat_name ()<< "_PROXY_FACTORY_ADAPTER;"<<be_nl << be_nl;

      *os << "class " << be_global->stub_export_macro ()<< " "
          << "TAO_"<< node->flat_name ()
          << "_Smart_Proxy_Base" << be_idt_nl
          << ": public virtual "
          << bt->nested_type_name (this->ctx_->scope ());


      if (node->n_inherits () > 0)  // node interface inherits from other
        // interfaces
        {
          long i;
          for (i = 0; i < node->n_inherits (); i++)
            {
              be_interface *inherited =
                be_interface::narrow_from_decl (node->inherits ()[i]);
              be_decl *scope = 0;
              if (inherited->is_nested ())
                {
                  // inherited node is used in the scope of "node" node
                  scope =
                    be_scope::narrow_from_scope (node->defined_in ())->decl ();
                }

              *os << "," << be_nl << "  public virtual ";
              *os << inherited->nested_sp_type_name (scope,"_Smart_Proxy_Base");  // dump the scoped name
            }  // end of for loop
        }
      else
        {
          *os << "," << be_nl << "  public virtual TAO_Smart_Proxy_Base";
        }
      *os << be_uidt_nl;

      *os << "{" << be_nl
          << "public:" << be_idt_nl
          << "TAO_"<< node->flat_name () << "_Smart_Proxy_Base (void);" << be_nl
        // Just to keep Old g++ complier (version: 2.7.2.3) happy its necessary
        // to declare and define the destructor explicitly.
          << "~TAO_"<< node->flat_name () << "_Smart_Proxy_Base (void);"<<be_nl
        // This method will delegate this method to the <base_proxy_>
        // member of the smart proxy and so the smart proxy's (nil)
        // stubobj will not be returned.
          << "virtual TAO_Stub *_stubobj (void) const;"
          << be_uidt_nl;

      // generate code for the interface definition by traversing thru the
      // elements of its scope. We depend on the front-end to have made sure
      // that only legal syntactic elements appear in our scope.

      os->indent ();
      if (this->visit_scope (node) == -1)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "(%N:%l) be_visitor_interface_ch::"
                             "visit_interface - "
                             "codegen for scope failed\n"), -1);
        }

      *os << "protected:" << be_idt_nl
          << "::" << node->full_name ()
          << "_ptr get_proxy (void);" << be_nl
          << "::" << node->full_name () << "_var proxy_;"
          << be_uidt_nl
          << "};\n\n";
    }
  else
    {
      ACE_UNUSED_ARG (node);
    }

  return 0;

}
