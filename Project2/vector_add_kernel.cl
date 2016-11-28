__kernel void vector_add(__global const int *in0, __global const int *in1,__global const int *in2, __global int *out,__global int *temp) {
    
    // Get the index of the current element to be processed
    int i = get_global_id(0);
    
    // Do the operation
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i];
            break;
        case 1: temp[i] = in0[(list_size)-1]*in1[i-1]*in2[i];
            break;
        default: temp[i] = in0[i-2]*in1[i-1]*in2[i];
    }
    
    
    //  temp[i] = in0[i]*in1[i]*in2[i];
    
    barrier(CLK_LOCAL_MEM_FENCE);
    //C[i]=T[i];
    out[i]=out[i]+temp[i];
}
