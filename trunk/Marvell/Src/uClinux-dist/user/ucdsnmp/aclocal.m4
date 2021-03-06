dnl AC_PROMPT_USER_NO_DEFINE(VARIABLE,PROMPT,[DEFAULT])
AC_DEFUN(AC_PROMPT_USER_NO_DEFINE,
dnl changequote(<<, >>) dnl
dnl <<
[
if test "x$defaults" = "xno"; then
echo $ac_n "$2 ($3): $ac_c"
read tmpinput
if test "$tmpinput" = "" -a "$3" != ""; then
  tmpinput="$3"
fi
eval $1=\"$tmpinput\"
else
tmpinput="$3"
eval $1=\"$tmpinput\"
fi
]
dnl >>
dnl changequote([, ])
) dnl done AC_PROMPT_USER

AC_DEFUN(AC_PROMPT_USER,
[
MSG_CHECK=`echo "$2" | tail -1`
AC_CACHE_CHECK($MSG_CHECK, ac_cv_user_prompt_$1,
[echo ""
AC_PROMPT_USER_NO_DEFINE($1,[$2],$3)
eval ac_cv_user_prompt_$1=\$$1
echo $ac_n "setting $MSG_CHECK to...  $ac_c"
])
if test "$ac_cv_user_prompt_$1" != "none"; then
  if test "$4" != ""; then
    AC_DEFINE_UNQUOTED($1,"$ac_cv_user_prompt_$1")
  else
    AC_DEFINE_UNQUOTED($1,$ac_cv_user_prompt_$1)
  fi
fi
]) dnl

dnl AC_CHECK_STRUCT_FOR(INCLUDES,STRUCT,MEMBER,DEFINE,[no])
AC_DEFUN(AC_CHECK_STRUCT_FOR,[

ac_safe_struct=`echo "$2" | sed 'y%./+-%__p_%'`
ac_safe_member=`echo "$3" | sed 'y%./+-%__p_%'`
ac_safe_all="ac_cv_struct_${ac_safe_struct}_has_${ac_safe_member}"
changequote(, )dnl
  ac_uc_define=STRUCT_`echo "${ac_safe_struct}_HAS_${ac_safe_member}" | sed 'y%abcdefghijklmnopqrstuvwxyz./-%ABCDEFGHIJKLMNOPQRSTUVWXYZ___%'`
changequote([, ])dnl

AC_MSG_CHECKING([for $2.$3])
AC_CACHE_VAL($ac_safe_all,
[
if test "x$4" = "x"; then
  defineit="= 0"
elif test "x$4" = "xno"; then
  defineit=""
else
  defineit="$4"
fi
AC_TRY_COMPILE([
$1
],[
struct $2 testit; 
testit.$3 $defineit;
], eval "${ac_safe_all}=yes", eval "${ac_safe_all}=no" )
])

if eval "test \"x$`echo ${ac_safe_all}`\" = \"xyes\""; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED($ac_uc_define)
else
  AC_MSG_RESULT(no)
fi

])

dnl AC_CHECK_IFNET_FOR(SUBSTRUCT,[no])
AC_DEFUN(AC_CHECK_IFNET_FOR,[
dnl check for $1 in struct ifnet
AC_CHECK_STRUCT_FOR([
#ifdef IFNET_NEEDS_KERNEL
#define _KERNEL 1
#endif
#include <sys/types.h>
#include <sys/socket.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <net/if.h>
#ifdef HAVE_NET_IF_VAR_H
#include <net/if_var.h>
#endif
#ifdef HAVE_SYS_QUEUE_H
#include <sys/queue.h>
#endif
#ifdef linux
struct ifnet {
	char	*if_name;		/* name, e.g. ``en'' or ``lo'' */
	short	if_unit;		/* sub-unit for lower level driver */
	short	if_mtu;			/* maximum transmission unit */
	short	if_flags;		/* up/down, broadcast, etc. */
	int	if_metric;		/* routing metric (external only) */
	char    if_hwaddr [6];		/* ethernet address */
	int	if_type;		/* interface type: 1=generic,
					   28=slip, ether=6, loopback=24 */
	int	if_speed;		/* interface speed: in bits/sec */

	struct sockaddr if_addr;	/* interface's address */
	struct sockaddr ifu_broadaddr;	/* broadcast address */
	struct sockaddr ia_subnetmask; 	/* interface's mask */

	struct	ifqueue {
		int	ifq_len;
		int	ifq_drops;
	} if_snd;			/* output queue */
	int	if_ibytes;		/* octets received on interface */
	int	if_ipackets;		/* packets received on interface */
	int	if_ierrors;		/* input errors on interface */
	int	if_obytes;		/* octets sent on interface */
	int	if_opackets;		/* packets sent on interface */
	int	if_oerrors;		/* output errors on interface */
	int	if_collisions;		/* collisions on csma interfaces */
/* end statistics */
	struct	ifnet *if_next;
};
#endif
], ifnet, $1, $2)
])

dnl
dnl Add a search path to the LIBS and CFLAGS variables
dnl
AC_DEFUN(AC_ADD_SEARCH_PATH,[
  if test "x$1" != x -a -d $1; then
     if test -d $1/lib; then
       LDFLAGS="-L$1/lib $LDFLAGS"
     fi
     if test -d $1/include; then
	CPPFLAGS="-I$1/include $CPPFLAGS"
     fi
  fi
])
