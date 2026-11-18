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
#define IPA_SZ_48       (5ULL << 32)

/* Translation Granule */
#define TG0_SHIFT       14
#define TG1_SHIFT       30

#define TG1             (0ULL << TG1_SHIFT)
#define TG0             (0ULL << TG0_SHIFT)

/* TxSZ Size of the significant bit check */
#define T0SZ_SHIFT      0
#define T1SZ_SHIFT      16

#define T0SZ            (16ULL << T0SZ_SHIFT)
#define T1SZ            (16ULL << T1SZ_SHIFT)

/* Cacheable Properties */
#define INNER_NC        (0ULL)     /* Inner Non-cacheable */
#define INNER_WB_WA_C   (1ULL)     /* Inner Write-Back Write-Allocate */
#define INNER_WT_C      (2ULL)     /* Inner Write-Through  Cacheable */
#define INNER_WB_NW_C   (3ULL)     /* Inner Write-Back no Write-Allocate Cacheable */

#define IRGN0           (INNER_WB_WA_C << 8)
#define ORGN0           (INNER_WB_WA_C << 10)

/* Shareability */
#define NO_SHARE        (0ULL)
#define UNPREDICTABLE   (1ULL)
#define OUT_SHARE       (2ULL)
#define IN_SHARE        (3ULL)

#define SH0             (IN_SHARE << 12)

/* TCR Settings assembled to configure the MMU */
#define TCR_SETTINGS    (T0SZ | IRGN0 | ORGN0 | SH0  | TG0 | IPA_SZ )

/* MAIR slots */
#define MAIR_SLOT_0(x)  (x << 0)    /* MAIR_D_nGnRnE */
#define MAIR_SLOT_1(x)  (x << 8)    /* MAIR_D_NORMAL */
#define MAIR_SLOT_2(x)  (x << 16)   /* available */
#define MAIR_SLOT_3(x)  (x << 24)   /* available */
#define MAIR_SLOT_4(x)  (x << 32)   /* available */
#define MAIR_SLOT_5(x)  (x << 40)   /* available */
#define MAIR_SLOT_6(x)  (x << 48)   /* available */
#define MAIR_SLOT_7(x)  (x << 56)   /* available */


/* Memory Types for MAIR */
#define MAIR_D_nGnRnE   (0x00UL) /* slot 0 */
#define MAIR_D_NORMAL   (0xFFUL) /* slot 1 */

/*Setting up MAIR*/
#define MAIR_SET        (MAIR_SLOT_0(MAIR_D_nGnRnE) | MAIR_SLOT_1(MAIR_D_NORMAL))

void mmu_init(void);

#endif /* MMU_H */
