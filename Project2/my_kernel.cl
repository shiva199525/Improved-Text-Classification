__kernel void 2gram(__global const int *in0,
                    __global const int *in1,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-1]*in1[i];
            break;
        default: temp[i] = in0[i-1]*in1[i];
    }
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}


__kernel void 3gram(__global const int *in0, __global const int *in1,__global const int *in2, __global int *out,__global int *temp) {
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i];
            break;
        case 1: temp[i] = in0[(list_size)-1]*in1[i-1]*in2[i];
            break;
        default: temp[i] = in0[i-2]*in1[i-1]*in2[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    out[i]=out[i]+temp[i];
}


__kernel void 7gram(__global const int *in0,
                    __global const int *in1,
                    __global const int *in2,
                    __global const int *in3,
                    __global const int *in4,
                    __global const int *in5,
                    __global const int *in6,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-6]*in1[(list_size)-5]*in2[(list_size)-4]*in3[(list_size)-3]*in4[(list_size)-2]*in5[(list_size)-1]*in6[i];
            break;
        case 1: temp[i] = in0[(list_size)-5]*in1[(list_size)-4]*in2[(list_size)-3]*in3[(list_size)-2]*in4[(list_size)-1]*in5[i-1]*in6[i];
            break;
        case 2: temp[i] = in0[(list_size)-4]*in1[(list_size)-3]*in2[(list_size)-2]*in3[(list_size)-1]*in4[i-2]*in5[i-1]*in6[i];
            break;
        case 3: temp[i] = in0[(list_size)-3]*in1[(list_size)-2]*in2[(list_size)-1]*in3[i-3]*in4[i-2]*in5[i-1]*in6[i];
            break;
        case 4: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i-4]*in3[i-3]*in4[i-2]*in5[i-1]*in6[i];
            break;
        case 5: temp[i] = in0[(list_size)-1]*in1[i-5]*in2[i-4]*in3[i-3]*in4[i-2]*in5[i-1]*in6[i];
            break;
        default: temp[i] = in0[i-6]*in1[i-5]*in2[i-4]*in3[i-3]*in4[i-2]*in5[i-1]*in6[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}


__kernel void 6gram(__global const int *in0,
                    __global const int *in1,
                    __global const int *in2,
                    __global const int *in3,
                    __global const int *in4,
                    __global const int *in5,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-5]*in1[(list_size)-4]*in2[(list_size)-3]*in3[(list_size)-2]*in4[(list_size)-1]*in5[i];
            break;
        case 1: temp[i] = in0[(list_size)-4]*in1[(list_size)-3]*in2[(list_size)-2]*in3[(list_size)-1]*in4[i-1]*in5[i];
            break;
        case 2: temp[i] = in0[(list_size)-3]*in1[(list_size)-2]*in2[(list_size)-1]*in3[i-2]*in4[i-1]*in5[i];
            break;
        case 3: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i-3]*in3[i-2]*in4[i-1]*in5[i];
            break;
        case 4: temp[i] = in0[(list_size)-1]*in1[i-4]*in2[i-3]*in3[i-2]*in4[i-1]*in5[i];
            break;
        default: temp[i] = in0[i-5]*in1[i-4]*in2[i-3]*in3[i-2]*in4[i-1]*in5[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}


__kernel void 8gram(__global const int *in0,
                    __global const int *in1,
                    __global const int *in2,
                    __global const int *in3,
                    __global const int *in4,
                    __global const int *in5,
                    __global const int *in6,
                    __global const int *in7,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-7]*in1[(list_size)-6]*in2[(list_size)-5]*in3[(list_size)-4]*in4[(list_size)-3]*in5[(list_size)-2]*in6[(list_size)-1]*in7[i];
            break;
        case 1: temp[i] = in0[(list_size)-6]*in1[(list_size)-5]*in2[(list_size)-4]*in3[(list_size)-3]*in4[(list_size)-2]*in5[(list_size)-1]*in6[i-1]*in7[i];
            break;
        case 2: temp[i] = in0[(list_size)-5]*in1[(list_size)-4]*in2[(list_size)-3]*in3[(list_size)-2]*in4[(list_size)-1]*in5[i-2]*in6[i-1]*in7[i];
            break;
        case 3: temp[i] = in0[(list_size)-4]*in1[(list_size)-3]*in2[(list_size)-2]*in3[(list_size)-1]*in4[i-3]*in5[i-2]*in6[i-1]*in7[i];
            break;
        case 4: temp[i] = in0[(list_size)-3]*in1[(list_size)-2]*in2[(list_size)-1]*in3[i-4]*in4[i-3]*in5[i-2]*in6[i-1]*in7[i];
            break;
        case 5: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i-5]*in3[i-4]*in4[i-3]*in5[i-2]*in6[i-1]*in7[i];
            break;
        case 6: temp[i] = in0[(list_size)-1]*in1[i-6]*in2[i-5]*in3[i-4]*in4[i-3]*in5[i-2]*in6[i-1]*in7[i];
            break;
        default: temp[i] = in0[i-7]*in1[i-6]*in2[i-5]*in3[i-4]*in4[i-3]*in5[i-2]*in6[i-1]*in7[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}


__kernel void 5gram(__global const int *in0,
                    __global const int *in1,
                    __global const int *in2,
                    __global const int *in3,
                    __global const int *in4,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-4]*in1[(list_size)-3]*in2[(list_size)-2]*in3[(list_size)-1]*in4[i];
            break;
        case 1: temp[i] = in0[(list_size)-3]*in1[(list_size)-2]*in2[(list_size)-1]*in3[i-1]*in4[i];
            break;
        case 2: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i-2]*in3[i-1]*in4[i];
            break;
        case 3: temp[i] = in0[(list_size)-1]*in1[i-3]*in2[i-2]*in3[i-1]*in4[i];
            break;
        default: temp[i] = in0[i-4]*in1[i-3]*in2[i-2]*in3[i-1]*in4[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}


__kernel void 4gram(__global const int *in0,
                    __global const int *in1,
                    __global const int *in2,
                    __global const int *in3,
                    __global int *out,
                    __global int *temp)

{
    
    int i = get_global_id(0);
    
    
    int list_size = 1024*10;
    
    switch(i){
        case 0: temp[i] = in0[(list_size)-3]*in1[(list_size)-2]*in2[(list_size)-1]*in3[i];
            break;
        case 1: temp[i] = in0[(list_size)-2]*in1[(list_size)-1]*in2[i-1]*in3[i];
            break;
        case 2: temp[i] = in0[(list_size)-1]*in1[i-2]*in2[i-1]*in3[i];
            break;
        default: temp[i] = in0[i-3]*in1[i-2]*in2[i-1]*in3[i];
    }
    
    
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    out[i]=out[i]+temp[i];
}
