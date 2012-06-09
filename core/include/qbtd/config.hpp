#ifndef QBTD_CONFIG_HPP
#define QBTD_CONFIG_HPP

#ifdef QBTD_LIBRARY
#define QBTD_DLL Q_DECL_EXPORT
#else
#define QBTD_DLL Q_DECL_IMPORT
#endif

#endif
