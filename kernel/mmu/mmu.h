#ifndef MMU_H
#define MMU_H
/**
 * This header file will define most of the settings available
 * that we can use to configure the arm64 mmu to our liking.
 */




/**
 * TCR_EL1 has a format looking like this:
 * 63             48   34   32 3130        21  16 15 14        5    0
 * +----------------------------------------------------------------+
 * | TTBR_SELECT   |   |IPA SZ|TG1|        | T1SZ | TG0|       |T0SZ|
 * +----------------------------------------------------------------+
 * Reading the ARM documentation there are a few settings we can configure.
 */

/* Intermediate Physical Address Size */
#define IPA_SZ_SHIFT    32
#define IPA_SZ_32       (0ULL << IPA_SZ_SHIFT)
#define IPA_SZ_48       (5ULL << IPA_SZ_SHIFT)

/* Translation Granule */
#define TG0_SHIFT       14
#define TG1_SHIFT       30

#define TG_4            (0ULL)
#define TG_16           (1ULL)
#define TG_64           (3ULL)

#define TG1_SET(x)      (x << TG1_SHIFT)
#define TG0_SET(x)      (x << TG0_SHIFT)

/* TxSZ Size of the significant bit check */
#define T0SZ_SHIFT      0
#define T1SZ_SHIFT      16

#define T0SZ_SET(x)     (x << T0SZ_SHIFT)
#define T1SZ_SET(x)     (x << T1SZ_SHIFT)

/* Cacheable Properties */
#define INNER_NC        (0ULL)     /* Inner Non-cacheable */
#define INNER_WB_WA_C   (1ULL)     /* Inner Write-Back Write-Allocate */
#define INNER_WT_C      (2ULL)     /* Inner Write-Through  Cacheable */
#define INNER_WB_NW_C   (3ULL)     /* Inner Write-Back no Write-Allocate Cacheable */

/* Shareability */
#define NO_SHARE        (0ULL << 12)
#define UNPREDICTABLE   (1ULL << 12)
#define OUT_SHARE       (2ULL << 12)
#define IN_SHARE        (3ULL << 12)

#endif /* MMU_H */
