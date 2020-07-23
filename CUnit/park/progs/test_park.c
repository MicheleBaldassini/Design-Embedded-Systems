
#include <stdio.h>  
#include <string.h>
#include "/home/michele/CUnit/CUnit/Headers/Basic.h"
#include "types.h"
#include "park.h"
#include "globals.h"

void EE_lcd_putc (char a){
  fprintf (stderr, "Park is '%c'", a);
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  printf ("\nInitializing suite1\n");
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  printf ("\nCompleting suite1\n");
  return 0;
}

void testInit(void) {
	Park p;
	ParkInit(&p);
	CU_ASSERT(0 == isbusy);
}

void testParkDispatch(void) {
	int i;	
	Park p;
	ParkInit(&p);
	for(i = 1;i < 3;i++) {
		ParkTran_(&p, i); 	// transizione 
		libero = 1;	// setto evento in modo che dispatch possa far cambiare lo
		occupato = 1;	// stato in base al valore dei segnali libero, occupato, 
		accetto = 1;	
		ParkDispatch(&p); 
		if(i < 3){
			CU_ASSERT(p.state_ == (i+1));
		} else {
			CU_ASSERT(p.state_ == 0);
		} 
	}
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of ParkinInit(Park *)", testInit)) 
       || (NULL == CU_add_test(pSuite, "test of ParkDispatch(Park *)", testParkDispatch)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

