/*$T Common/Atomic.h GC 1.140 10/10/07 10:06:26 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __70YX_ATOMIC_H__
#define __70YX_ATOMIC_H__

#define ATOMIC_INIT(i)	{ (i) }

/*
 =======================================================================================================================
        atomic_read - read atomic variable @v: pointer of type atomic_t Atomically reads the value of @v.
 =======================================================================================================================
 */
#define atomic_read(v)	((v)->counter)

/*
 =======================================================================================================================
        atomic_set - set atomic variable @v: pointer of type atomic_t @i: required value Atomically sets the value of
        @v to @i.
 =======================================================================================================================
 */
#define atomic_set(v, i)	(((v)->counter) = (i))

#endif