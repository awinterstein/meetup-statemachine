#ifndef _MACRO_PUSH_H_
#define _MACRO_PUSH_H_

#ifdef ADC0
	#pragma push_macro("ADC0")
	#undef ADC0
	#define ADC0 ADC0_BASE
	#define RESTORE_ADC0
#endif

#ifdef GPIOA
	#pragma push_macro("GPIOA")
	#undef GPIOA
	#define GPIOA GPIOA_BASE
	#define RESTORE_GPIOA
#endif

#ifdef GPIOB
	#pragma push_macro("GPIOB")
	#undef GPIOB
	#define GPIOB GPIOB_BASE
	#define RESTORE_GPIOB
#endif

#ifdef GPIOC
	#pragma push_macro("GPIOC")
	#undef GPIOC
	#define GPIOC GPIOC_BASE
	#define RESTORE_GPIOC
#endif

#ifdef GPIOD
	#pragma push_macro("GPIOD")
	#undef GPIOD
	#define GPIOD GPIOD_BASE
	#define RESTORE_GPIOD
#endif

#ifdef GPIOE
	#pragma push_macro("GPIOE")
	#undef GPIOE
	#define GPIOE GPIOE_BASE
	#define RESTORE_GPIOE
#endif

#endif // _MACRO_PUSH_H_
