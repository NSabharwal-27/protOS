#ifndef MMU_H
#define MMU_H
/**
 * This header file will define most of the settings available
 * that we can use to configure the arm64 mmu to our liking.
 */

/**
 * TCR_EL1 has a format looking like this:
 * 63                  34   32 3130        21  16 15 14        5    0
 * +----------------------------------------------------------------+
 * | TTBR_SELECT   |   |IPA SZ|TG1|        | T1SZ | TG0|       |T0SZ|
 * +----------------------------------------------------------------+
 * Reading the ARM documentation there are a few settings we can configure.
 */

/* Intermediate Physical Address Size */
#define IPA_SZ_SHIFT    32
#define IPA_SZ_32       (0 << IPA_SZ_SHIFT)
#define IPA_SZ_48       (5 << IPA_SZ_SHIFT)

/* Translation Granule */
#define TG0_SHIFT       14
#define TG1_SHIFT       30

#define TG_4            (0)
#define TG_16           (1)
#define TG_64           (3)

#define TG1_SET(x)      (x << TG1_SHIFT)
#define TG0_SET(x)      (x << TG0_SHIFT)

/* TxSZ Size of the significant bit check */
#define T0SZ_SHIFT      0
#define T1SZ_SHIFT      16

#define T0SZ_SET(x)     (x << T0SZ_SHIFT)
#define T1SZ_SET(x)     (x << T1SZ_SHIFT)



#endif /* MMU_H */
