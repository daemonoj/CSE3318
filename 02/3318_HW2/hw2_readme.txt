Compilation instructions to run my code:
gcc hw2_list.c list.c
(or include a makefile)

I ran my code on:
- omega

I ran my code with Valgrind: 
- Yes

My code runs with the input files (select what applies to you):
- Unix version


For the answers below assume L1 has size N1 and L2 has size N2.
If you call any of the functions from the provided list.c (e.g. destroy_list), give the time complexity for them.

merge(L1, L2) 
	time: O( N1 + N2 )
	space: O( 1 ) 

check_sorted(L1) 
	time: O(  N1  )
	space: O( 1 ) 

print_list_with_addresses(L1) 
	time: O(  N1  )
	space: O( 1 )
	
remove_duplicates(L1) 
	time: O(  N1  )
	space: O( 1 )

destroy_list(L1) 
	time: O(  N1  )
	space: O( 1 )




