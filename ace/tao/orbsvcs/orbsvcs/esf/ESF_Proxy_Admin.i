// ESF_Proxy_Admin.i,v 1.4 2001/05/11 17:18:40 bala Exp

template<class EC,class P,class I> ACE_INLINE void
TAO_ESF_Proxy_Admin<EC,P,I>::
    for_each (TAO_ESF_Worker<P> *worker,
              CORBA::Environment &ACE_TRY_ENV)
      ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->collection_->for_each (worker, ACE_TRY_ENV);
}
