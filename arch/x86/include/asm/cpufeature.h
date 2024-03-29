#ifndef _ASM_X86_CPUFEATURE_H
#define _ASM_X86_CPUFEATURE_H

#include <asm/processor.h>

#if defined(__KERNEL__) && !defined(__ASSEMBLY__)

#include <asm/asm.h>
#include <linux/bitops.h>

enum cpuid_leafs
{
	CPUID_1_EDX		= 0,
	CPUID_8000_0001_EDX,
	CPUID_8086_0001_EDX,
	CPUID_LNX_1,
	CPUID_1_ECX,
	CPUID_C000_0001_EDX,
	CPUID_8000_0001_ECX,
	CPUID_LNX_2,
	CPUID_LNX_3,
	CPUID_7_0_EBX,
	CPUID_D_1_EAX,
	CPUID_F_0_EDX,
	CPUID_F_1_EDX,
	CPUID_8000_0008_EBX,
	CPUID_6_EAX,
	CPUID_8000_000A_EDX,
	CPUID_7_ECX,
	CPUID_8000_0007_EBX,
	CPUID_7_EDX,
};

#ifdef CONFIG_X86_FEATURE_NAMES
extern const char * const x86_cap_flags[NCAPINTS*32];
extern const char * const x86_power_flags[32];
#define X86_CAP_FMT "%s"
#define x86_cap_flag(flag) x86_cap_flags[flag]
#else
#define X86_CAP_FMT "%d:%d"
#define x86_cap_flag(flag) ((flag) >> 5), ((flag) & 31)
#endif

/*
 * In order to save room, we index into this array by doing
 * X86_BUG_<name> - NCAPINTS*32.
 */
extern const char * const x86_bug_flags[NBUGINTS*32];

#define test_cpu_cap(c, bit)						\
	 test_bit(bit, (unsigned long *)((c)->x86_capability))

#define REQUIRED_MASK_BIT_SET(bit)					\
	 ( (((bit)>>5)==0  && (1UL<<((bit)&31) & REQUIRED_MASK0 )) ||	\
	   (((bit)>>5)==1  && (1UL<<((bit)&31) & REQUIRED_MASK1 )) ||	\
	   (((bit)>>5)==2  && (1UL<<((bit)&31) & REQUIRED_MASK2 )) ||	\
	   (((bit)>>5)==3  && (1UL<<((bit)&31) & REQUIRED_MASK3 )) ||	\
	   (((bit)>>5)==4  && (1UL<<((bit)&31) & REQUIRED_MASK4 )) ||	\
	   (((bit)>>5)==5  && (1UL<<((bit)&31) & REQUIRED_MASK5 )) ||	\
	   (((bit)>>5)==6  && (1UL<<((bit)&31) & REQUIRED_MASK6 )) ||	\
	   (((bit)>>5)==7  && (1UL<<((bit)&31) & REQUIRED_MASK7 )) ||	\
	   (((bit)>>5)==8  && (1UL<<((bit)&31) & REQUIRED_MASK8 )) ||	\
	   (((bit)>>5)==9  && (1UL<<((bit)&31) & REQUIRED_MASK9 )) ||	\
	   (((bit)>>5)==10 && (1UL<<((bit)&31) & REQUIRED_MASK10)) ||	\
	   (((bit)>>5)==11 && (1UL<<((bit)&31) & REQUIRED_MASK11)) ||	\
	   (((bit)>>5)==12 && (1UL<<((bit)&31) & REQUIRED_MASK12)) ||	\
	   (((bit)>>5)==13 && (1UL<<((bit)&31) & REQUIRED_MASK13)) ||	\
	   (((bit)>>5)==14 && (1UL<<((bit)&31) & REQUIRED_MASK14)) ||	\
	   (((bit)>>5)==15 && (1UL<<((bit)&31) & REQUIRED_MASK15)) ||	\
	   (((bit)>>5)==16 && (1UL<<((bit)&31) & REQUIRED_MASK16)) ||	\
	   (((bit)>>5)==17 && (1UL<<((bit)&31) & REQUIRED_MASK17)) ||	\
	   (((bit)>>5)==18 && (1UL<<((bit)&31) & REQUIRED_MASK18)) )

#define DISABLED_MASK_BIT_SET(bit)					\
	 ( (((bit)>>5)==0  && (1UL<<((bit)&31) & DISABLED_MASK0 )) ||	\
	   (((bit)>>5)==1  && (1UL<<((bit)&31) & DISABLED_MASK1 )) ||	\
	   (((bit)>>5)==2  && (1UL<<((bit)&31) & DISABLED_MASK2 )) ||	\
	   (((bit)>>5)==3  && (1UL<<((bit)&31) & DISABLED_MASK3 )) ||	\
	   (((bit)>>5)==4  && (1UL<<((bit)&31) & DISABLED_MASK4 )) ||	\
	   (((bit)>>5)==5  && (1UL<<((bit)&31) & DISABLED_MASK5 )) ||	\
	   (((bit)>>5)==6  && (1UL<<((bit)&31) & DISABLED_MASK6 )) ||	\
	   (((bit)>>5)==7  && (1UL<<((bit)&31) & DISABLED_MASK7 )) ||	\
	   (((bit)>>5)==8  && (1UL<<((bit)&31) & DISABLED_MASK8 )) ||	\
	   (((bit)>>5)==9  && (1UL<<((bit)&31) & DISABLED_MASK9 )) ||	\
	   (((bit)>>5)==10 && (1UL<<((bit)&31) & DISABLED_MASK10)) ||	\
	   (((bit)>>5)==11 && (1UL<<((bit)&31) & DISABLED_MASK11)) ||	\
	   (((bit)>>5)==12 && (1UL<<((bit)&31) & DISABLED_MASK12)) ||	\
	   (((bit)>>5)==13 && (1UL<<((bit)&31) & DISABLED_MASK13)) ||	\
	   (((bit)>>5)==14 && (1UL<<((bit)&31) & DISABLED_MASK14)) ||	\
	   (((bit)>>5)==15 && (1UL<<((bit)&31) & DISABLED_MASK15)) ||	\
	   (((bit)>>5)==16 && (1UL<<((bit)&31) & DISABLED_MASK16)) ||	\
	   (((bit)>>5)==17 && (1UL<<((bit)&31) & DISABLED_MASK17)) ||	\
	   (((bit)>>5)==18 && (1UL<<((bit)&31) & DISABLED_MASK18)) )

#define cpu_has(c, bit)							\
	(__builtin_constant_p(bit) && REQUIRED_MASK_BIT_SET(bit) ? 1 :	\
	 test_cpu_cap(c, bit))

#define this_cpu_has(bit)						\
	(__builtin_constant_p(bit) && REQUIRED_MASK_BIT_SET(bit) ? 1 : 	\
	 x86_this_cpu_test_bit(bit, (unsigned long *)&cpu_info.x86_capability))

/*
 * This macro is for detection of features which need kernel
 * infrastructure to be used.  It may *not* directly test the CPU
 * itself.  Use the cpu_has() family if you want true runtime
 * testing of CPU features, like in hypervisor code where you are
 * supporting a possible guest feature where host support for it
 * is not relevant.
 */
#define cpu_feature_enabled(bit)	\
	(__builtin_constant_p(bit) && DISABLED_MASK_BIT_SET(bit) ? 0 :	\
	 cpu_has(&boot_cpu_data, bit))

#define boot_cpu_has(bit)	cpu_has(&boot_cpu_data, bit)

#define set_cpu_cap(c, bit)	set_bit(bit, (unsigned long *)((c)->x86_capability))
#define clear_cpu_cap(c, bit)	clear_bit(bit, (unsigned long *)((c)->x86_capability))
#define setup_clear_cpu_cap(bit) do { \
	clear_cpu_cap(&boot_cpu_data, bit);	\
	set_bit(bit, (unsigned long *)cpu_caps_cleared); \
} while (0)
#define setup_force_cpu_cap(bit) do { \
	set_cpu_cap(&boot_cpu_data, bit);	\
	set_bit(bit, (unsigned long *)cpu_caps_set);	\
} while (0)

#define setup_force_cpu_bug(bit) setup_force_cpu_cap(bit)

#define cpu_has_fpu		boot_cpu_has(X86_FEATURE_FPU)
#define cpu_has_pse		boot_cpu_has(X86_FEATURE_PSE)
#define cpu_has_tsc		boot_cpu_has(X86_FEATURE_TSC)
#define cpu_has_pge		boot_cpu_has(X86_FEATURE_PGE)
#define cpu_has_apic		boot_cpu_has(X86_FEATURE_APIC)
#define cpu_has_fxsr		boot_cpu_has(X86_FEATURE_FXSR)
#define cpu_has_xmm		boot_cpu_has(X86_FEATURE_XMM)
#define cpu_has_xmm2		boot_cpu_has(X86_FEATURE_XMM2)
#define cpu_has_aes		boot_cpu_has(X86_FEATURE_AES)
#define cpu_has_avx		boot_cpu_has(X86_FEATURE_AVX)
#define cpu_has_avx2		boot_cpu_has(X86_FEATURE_AVX2)
#define cpu_has_clflush		boot_cpu_has(X86_FEATURE_CLFLUSH)
#define cpu_has_gbpages		boot_cpu_has(X86_FEATURE_GBPAGES)
#define cpu_has_arch_perfmon	boot_cpu_has(X86_FEATURE_ARCH_PERFMON)
#define cpu_has_pat		boot_cpu_has(X86_FEATURE_PAT)
#define cpu_has_x2apic		boot_cpu_has(X86_FEATURE_X2APIC)
#define cpu_has_xsave		boot_cpu_has(X86_FEATURE_XSAVE)
#define cpu_has_xsaves		boot_cpu_has(X86_FEATURE_XSAVES)
#define cpu_has_osxsave		boot_cpu_has(X86_FEATURE_OSXSAVE)
#define cpu_has_hypervisor	boot_cpu_has(X86_FEATURE_HYPERVISOR)
/*
 * Do not add any more of those clumsy macros - use static_cpu_has_safe() for
 * fast paths and boot_cpu_has() otherwise!
 */

#if __GNUC__ >= 4
extern void warn_pre_alternatives(void);
extern bool __static_cpu_has_safe(u16 bit);

/*
 * Static testing of CPU features.  Used the same as boot_cpu_has().
 * These are only valid after alternatives have run, but will statically
 * patch the target code for additional performance.
 */
static __always_inline __pure bool __static_cpu_has(u16 bit)
{
#ifdef CC_HAVE_ASM_GOTO

#ifdef CONFIG_X86_DEBUG_STATIC_CPU_HAS

		/*
		 * Catch too early usage of this before alternatives
		 * have run.
		 */
		asm_volatile_goto("1: jmp %l[t_warn]\n"
			 "2:\n"
			 ".section .altinstructions,\"a\"\n"
			 " .long 1b - .\n"
			 " .long 0\n"		/* no replacement */
			 " .word %P0\n"		/* 1: do replace */
			 " .byte 2b - 1b\n"	/* source len */
			 " .byte 0\n"		/* replacement len */
			 " .byte 0\n"		/* pad len */
			 ".previous\n"
			 /* skipping size check since replacement size = 0 */
			 : : "i" (X86_FEATURE_ALWAYS) : : t_warn);

#endif

		asm_volatile_goto("1: jmp %l[t_no]\n"
			 "2:\n"
			 ".section .altinstructions,\"a\"\n"
			 " .long 1b - .\n"
			 " .long 0\n"		/* no replacement */
			 " .word %P0\n"		/* feature bit */
			 " .byte 2b - 1b\n"	/* source len */
			 " .byte 0\n"		/* replacement len */
			 " .byte 0\n"		/* pad len */
			 ".previous\n"
			 /* skipping size check since replacement size = 0 */
			 : : "i" (bit) : : t_no);
		return true;
	t_no:
		return false;

#ifdef CONFIG_X86_DEBUG_STATIC_CPU_HAS
	t_warn:
		warn_pre_alternatives();
		return false;
#endif

#else /* CC_HAVE_ASM_GOTO */

		u8 flag;
		/* Open-coded due to __stringify() in ALTERNATIVE() */
		asm volatile("1: movb $0,%0\n"
			     "2:\n"
			     ".section .altinstructions,\"a\"\n"
			     " .long 1b - .\n"
			     " .long 3f - .\n"
			     " .word %P1\n"		/* feature bit */
			     " .byte 2b - 1b\n"		/* source len */
			     " .byte 4f - 3f\n"		/* replacement len */
			     " .byte 0\n"		/* pad len */
			     ".previous\n"
			     ".section .discard,\"aw\",@progbits\n"
			     " .byte 0xff + (4f-3f) - (2b-1b)\n" /* size check */
			     ".previous\n"
			     ".section .altinstr_replacement,\"ax\"\n"
			     "3: movb $1,%0\n"
			     "4:\n"
			     ".previous\n"
			     : "=qm" (flag) : "i" (bit));
		return flag;

#endif /* CC_HAVE_ASM_GOTO */
}

#define static_cpu_has(bit)					\
(								\
	__builtin_constant_p(boot_cpu_has(bit)) ?		\
		boot_cpu_has(bit) :				\
	__builtin_constant_p(bit) ?				\
		__static_cpu_has(bit) :				\
		boot_cpu_has(bit)				\
)

static __always_inline __pure bool _static_cpu_has_safe(u16 bit)
{
#ifdef CC_HAVE_ASM_GOTO
		asm_volatile_goto("1: jmp %l[t_dynamic]\n"
			 "2:\n"
			 ".skip -(((5f-4f) - (2b-1b)) > 0) * "
			         "((5f-4f) - (2b-1b)),0x90\n"
			 "3:\n"
			 ".section .altinstructions,\"a\"\n"
			 " .long 1b - .\n"		/* src offset */
			 " .long 4f - .\n"		/* repl offset */
			 " .word %P1\n"			/* always replace */
			 " .byte 3b - 1b\n"		/* src len */
			 " .byte 5f - 4f\n"		/* repl len */
			 " .byte 3b - 2b\n"		/* pad len */
			 ".previous\n"
			 ".section .altinstr_replacement,\"ax\"\n"
			 "4: jmp %l[t_no]\n"
			 "5:\n"
			 ".previous\n"
			 ".section .altinstructions,\"a\"\n"
			 " .long 1b - .\n"		/* src offset */
			 " .long 0\n"			/* no replacement */
			 " .word %P0\n"			/* feature bit */
			 " .byte 3b - 1b\n"		/* src len */
			 " .byte 0\n"			/* repl len */
			 " .byte 0\n"			/* pad len */
			 ".previous\n"
			 : : "i" (bit), "i" (X86_FEATURE_ALWAYS)
			 : : t_dynamic, t_no);
		return true;
	t_no:
		return false;
	t_dynamic:
		return __static_cpu_has_safe(bit);
#else
		u8 flag;
		/* Open-coded due to __stringify() in ALTERNATIVE() */
		asm volatile("1: movb $2,%0\n"
			     "2:\n"
			     ".section .altinstructions,\"a\"\n"
			     " .long 1b - .\n"		/* src offset */
			     " .long 3f - .\n"		/* repl offset */
			     " .word %P2\n"		/* always replace */
			     " .byte 2b - 1b\n"		/* source len */
			     " .byte 4f - 3f\n"		/* replacement len */
			     " .byte 0\n"		/* pad len */
			     ".previous\n"
			     ".section .discard,\"aw\",@progbits\n"
			     " .byte 0xff + (4f-3f) - (2b-1b)\n" /* size check */
			     ".previous\n"
			     ".section .altinstr_replacement,\"ax\"\n"
			     "3: movb $0,%0\n"
			     "4:\n"
			     ".previous\n"
			     ".section .altinstructions,\"a\"\n"
			     " .long 1b - .\n"		/* src offset */
			     " .long 5f - .\n"		/* repl offset */
			     " .word %P1\n"		/* feature bit */
			     " .byte 4b - 3b\n"		/* src len */
			     " .byte 6f - 5f\n"		/* repl len */
			     " .byte 0\n"		/* pad len */
			     ".previous\n"
			     ".section .discard,\"aw\",@progbits\n"
			     " .byte 0xff + (6f-5f) - (4b-3b)\n" /* size check */
			     ".previous\n"
			     ".section .altinstr_replacement,\"ax\"\n"
			     "5: movb $1,%0\n"
			     "6:\n"
			     ".previous\n"
			     : "=qm" (flag)
			     : "i" (bit), "i" (X86_FEATURE_ALWAYS));
		return (flag == 2 ? __static_cpu_has_safe(bit) : flag);
#endif /* CC_HAVE_ASM_GOTO */
}

#define static_cpu_has_safe(bit)				\
(								\
	__builtin_constant_p(boot_cpu_has(bit)) ?		\
		boot_cpu_has(bit) :				\
		_static_cpu_has_safe(bit)			\
)
#else
/*
 * gcc 3.x is too stupid to do the static test; fall back to dynamic.
 */
#define static_cpu_has(bit)		boot_cpu_has(bit)
#define static_cpu_has_safe(bit)	boot_cpu_has(bit)
#endif

#define cpu_has_bug(c, bit)		cpu_has(c, (bit))
#define set_cpu_bug(c, bit)		set_cpu_cap(c, (bit))
#define clear_cpu_bug(c, bit)		clear_cpu_cap(c, (bit))

#define static_cpu_has_bug(bit)		static_cpu_has((bit))
#define static_cpu_has_bug_safe(bit)	static_cpu_has_safe((bit))
#define boot_cpu_has_bug(bit)		cpu_has_bug(&boot_cpu_data, (bit))

#define MAX_CPU_FEATURES		(NCAPINTS * 32)
#define cpu_have_feature		boot_cpu_has

#define CPU_FEATURE_TYPEFMT		"x86,ven%04Xfam%04Xmod%04X"
#define CPU_FEATURE_TYPEVAL		boot_cpu_data.x86_vendor, boot_cpu_data.x86, \
					boot_cpu_data.x86_model

#endif /* defined(__KERNEL__) && !defined(__ASSEMBLY__) */
#endif /* _ASM_X86_CPUFEATURE_H */
