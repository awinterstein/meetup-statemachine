#ifndef _MACRO_POP_H_
#define _MACRO_POP_H_

#ifdef RESTORE_ADC0
	#pragma pop_macro("ADC0")
#endif

#ifdef RESTORE_GPIOA
	#pragma pop_macro("GPIOA")
#endif

#ifdef RESTORE_GPIOB
	#pragma pop_macro("GPIOB")
#endif

#ifdef RESTORE_GPIOC
	#pragma pop_macro("GPIOC")
#endif

#ifdef RESTORE_GPIOD
	#pragma pop_macro("GPIOD")
#endif

#ifdef RESTORE_GPIOE
	#pragma pop_macro("GPIOE")
#endif

#ifdef RESTORE_PIT0
	#pragma pop_macro("PIT0")
#endif

#endif // _MACRO_POP_H_
