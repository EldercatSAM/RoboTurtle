void Move_backward(){
    #ifndef steps
    #define steps 8
    int ti[steps] = {50,150,50,150,50,150,50,150};
	int b[steps][ServoNum] = {
		1500,1800,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500,
		1500,2000,2000,1500,1000,1500,1500,1000,1000,1500,2000,1500,
		1500,2000,2000,1500,1000,1500,1500,1200,1000,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1200,1500,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,1800,2000,
		1500,2000,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500};
	for (int i=0;i<steps;i++)
		action(ti[i],b[i]);
	#endif
}