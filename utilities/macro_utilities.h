#ifndef _MACRO_UTILITIES_H_
#define _MACRO_UTILITIES_H_

#define CONCAT_NOEXP(x, y)	x##y
#define CONCAT_EXP(x, y)	CONCAT_NOEXP(x, y)

#endif // _MACRO_UTILITIES_H_
