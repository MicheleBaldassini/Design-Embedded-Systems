
#include <stdio.h>  
#include <string.h>
#include "/home/michele/CUnit/CUnit/Headers/Basic.h"
#include "types.h"
#include "filter.h"
#include "globals.h"

unsigned int time;

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
void testInitRise() {
	Filter f;
	time = HYSR05_TMAX;
	Filter_init(&f, 0);
	CU_ASSERT_FATAL(f.distance == 0);
}

void testFilterRise(void) {
	int i;	
	float old_dis;
	float raw_data;
	Filter f;
	Filter_init(&f,0);
	for(;time < HYSR05_TMAX;time++) {
		old_dis = f.distance;
		raw_data = Filter_GetRawData(&f);
		Filter_Read(&f);
		CU_ASSERT(raw_data > old_dis);
		CU_ASSERT(f.distance > old_dis); 
		CU_ASSERT(f.distance < raw_data);
		CU_ASSERT(f.distance < HYSR05_DMAX);
		CU_ASSERT(f.distance > 0);
	}
}

void testInitFall() {
	Filter f;
	time = HYSR05_TMAX;
	Filter_init(&f, HYSR05_DMAX);
	CU_ASSERT_FATAL(f.distance == HYSR05_DMAX);
}

void testFilterFall(void) {
	int i;	
	float old_dis;
	float raw_data;
	Filter f;
	Filter_init(&f, HYSR05_DMAX);
	for(;time > 0;time--) {
		old_dis = f.distance;
		raw_data = Filter_GetRawData(&f);
		Filter_Read(&f);
		CU_ASSERT(raw_data < old_dis);
		CU_ASSERT(f.distance < old_dis); 
		CU_ASSERT(f.distance > raw_data);
		CU_ASSERT(f.distance < HYSR05_DMAX);
		CU_ASSERT(f.distance > 0);
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
   if ((NULL == CU_add_test(pSuite, "Filter_Init(Filter *, 0)", testInitRise)) 
	|| (NULL == CU_add_test(pSuite, "Filter_Init(Filter *, HYSR05_DMAX)", testInitFall))
	|| (NULL == CU_add_test(pSuite, "Filter_Read_Rise(Filter *)", testFilterRise))
       	|| (NULL == CU_add_test(pSuite, "Filter_Read_Fall(Filter *)", testFilterFall))
		)
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

