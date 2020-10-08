#include "pimpl.h"

template <typename T>
pimpl<T>::pimpl() : impl( std::make_unique<T>() ) {
};

template <typename T>
pimpl<T>::~pimpl() {
	// Not necessary to implement because we're using a smart ptr
};

template <typename T>
T* pimpl<T>::operator->() {
	return impl.get();
}

template <typename T>
T&  pimpl<T>::operator*() {
	return *( impl.get() );
}

template <typename T>
template <typename ...Args>
pimpl<T>::pimpl(Args&&... args) : impl( std::make_unique<T>( std::forward<Args>(args)... ) ) {

};