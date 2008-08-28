
#ifndef _DYN_LINK_H
#define _DYN_LINK_H

#if !defined (_SCAN_EXPORT)

  #if ( defined (__MINGW32__) || defined (_MSC_VER) ) && defined (READLINE_DLL)
    #if defined (BUILDING_DLL)
      #define _RL_DLL __declspec (dllexport)
    #else
      #define _RL_DLL __declspec (dllimport)
    #endif	/* BUILDING_DLL  */
  #else
    #define _RL_DLL
  #endif	/* __MINGW32__ ... _DYNAMIC_LINK  */

  #define RL_VAR(type, name)             extern _RL_DLL type name
  #define RL_FUNC(type, name, args)      _RL_DLL type __cdecl name args

#endif	/* _SCAN_EXPORT */

#endif /* _DYN_LINK_H  */
