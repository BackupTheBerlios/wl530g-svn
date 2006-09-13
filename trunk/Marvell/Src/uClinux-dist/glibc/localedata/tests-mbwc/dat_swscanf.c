/*
 *  TEST SUITE FOR MB/WC FUNCTIONS IN CLIBRARY
 *
 *	 FILE:	dat_swscanf.c
 *
 *	 SWSCANF:  int	swscanf (const wchar_t *s, const wchar_t *fmt, ...);
 */


#include <errno.h>
#include <stdlib.h>
#include "tst_types.h"
#include "tgn_locdef.h"


TST_SWSCANF tst_swscanf_loc [] =
{
  {
    { Tswscanf, TST_LOC_de },
    {
      /*------------------------ 01 -----------------------*/
      { { {
	0x002D, 0x0031,		0x003A,	   /* %d: -1   */
	0x0032,			0x003A,	   /* %u:  2   */
	0x0033, 0x002C, 0x0033, 0x003A,	   /* %f:  3.3 */
	0x00E4,			0x003A,	   /* %c: '�'  */
	0x00C4, 0x00DC, 0x0000, 0x0000,	   /* %s: "��" */
      },
	  L"%d:%u:%f:%c:%s", 0
      },
	{ /* The fields are: err_val, ret_flag, ret_val,
	     val_int, val_uns, val_flt, val_c, val_s, val_S.  */
	  0,1,5,
	  -1, 2, 3.3, '�', "��", { 0x0000, },
	},
      },
      /*------------------------ 02 -----------------------*/
      { { {
	0x00E4, 0x00C4, 0x0000		       /* "��" */
      },
	  L"%lc", 'C'
      },
	{ 0,1,1,
	  0,0,0,0,"", { 0x00E4, 0x0000 },
	},
      },
      /*------------------------ 03 -----------------------*/
      { { {
	0x00E4, 0x00C4, 0x0000		       /* "��" */
      },
	  L"%ls", 'S'
      },
	{ 0,1,1,
	  0,0,0,0,"", { 0x00E4, 0x00C4, 0x0000 },
	},
      },
      /*------------------------ 04 -----------------------*/
      /* <NO_WAIVER> x 2 */
      { { {
	0x00E4, 0x00C4, 0x0000		       /* "��" */
      },
	  L"1%d:2%d:3%d:4%d:5%d:6%d:7%d:8%d:9%d", 0
      },
#ifdef SHOJI_IS_RIGHT
	{ 1,EINVAL,1,WEOF,
	  0,0,0,0,"", { 0x0000 },
#else
	{ 0,1,0,
	  0,0,0,0,"", { 0x0000 },
#endif
	},
      },
      /*---------------------------------------------------*/
      { is_last: 1}	/* Last element.  */
    }
  },
  {
    { Tswscanf, TST_LOC_enUS },
    {
      /*------------------------ 01 -----------------------*/
      { { { 0x002D, 0x0031,					    0x003A,
	    0x0032,						    0x003A,
	    0x0035, 0x0034, 0x002E, 0x0033, 0x0045, 0x002D, 0x0031, 0x003A,
	    0x0041,						    0x003A,
	    0x0061, 0x0062, 0x0000,				    0x0000,
      },
	  L"%d:%u:%f:%c:%s", 0
      },
	{ 0,1,5,
	  -1, 2, 5.43, 'A', "ab", { 0x0000 },
	},
      },
      /*------------------------ 02 -----------------------*/
      /* <NO_WAIVER> x 2 */
      { { {
	0x0063, 0x0064, 0x0000
      },
	  L"%C", 'C'
      },
	{ 0,1,1,
	  0,0,0,0,"", { 0x0063, 0x0000 },
	},
      },
      /*------------------------ 03 -----------------------*/
      { { {
	0x0063, 0x0064, 0x0000
      },
	  L"%S", 'S'
      },
	{ 0,1,1,
	  0,0,0,0,"", { 0x0063, 0x0064, 0x0000 },
	},
      },
      /*---------------------------------------------------*/
      { is_last: 1}	/* Last element.  */
    }
  },
  {
    { Tswscanf, TST_LOC_eucJP },
    {
      /*------------------------ 01 -----------------------*/
      { { { 0x002D, 0x0031,	    0x003A,
	    0x0032,		    0x003A,
	    0x0033, 0x002E, 0x0033, 0x003A,
	    0x0062,		    0x003A,
	    0x0061, 0x0062, 0x0000, 0x0000,
      },
	  L"%d:%u:%f:%c:%s", 0
      },
	{ 0,1,5,
	  -1, 2, 3.3, 'b', "ab", { 0x0000 }
	},
      },
      /*------------------------ 02 -----------------------*/
      { { {
	0x30A2, 0x30A4, 0x0000
      },
	  L"%ls", 'S'
      },
	{ 0,1,1,
	  0,0,0,0,"", { 0x30A2, 0x30A4, 0x0000 }
	},
      },
      /*------------------------ 03 -----------------------*/
      { { {
	0x0031,			0x003A,
	0x0030,			0x003A,
	0x0033, 0x002E, 0x0039, 0x003A,
	0x0061,			0x003A,
	0x0063, 0x0064, 0x0000, 0x0000,
      },
	  L"%2$d:%1$u:%3$f:%4$c:%5$s", 0
      },
	{ 0,1,5,
	  0, 1, 3.9, 'a', "cd", { 0x0000 }
	},
      },
#ifdef SHOJI_IS_RIGHT
      /* XXX This test does not make sense.  The format string is
	 L"\x1\x2\x25\x53" and it is supposed to match the words
	 0x30A2, 0x30A4, 0x0001.  */
      /*------------------------ 04 -----------------------*/
      /* <NO_WAIVER> x 2 */
      { { {
	0x30A2, 0x30A4, 0x0001, 0x0000
      },
	  { 0x0001,0x0002,0x0025,0x0053,0x0000 }, 'S'
      },
	{ EILSEQ,1,EOF,
	  0,0,0,0,"", { 0x0000 }
	},
      },
#endif
      /*---------------------------------------------------*/
      { is_last: 1}	/* Last element.  */
    }
  },
  {
    { Tswscanf, TST_LOC_end }
  }
};