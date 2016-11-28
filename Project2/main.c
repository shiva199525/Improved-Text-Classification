
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tinydir.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)
#define LIST_SIZE 1024*10

int *A,*B,*C,*D,*E,*F,*G,*H,*I,*J,*K,*L,*M ,*N,*O,*P,*Q ,*R,*S,*T,*U,*V,*W,*X,*Y,*Z,*Blank;

char *kernel_ptr, *source_ptr;
char *project_path= "/Users/anoja/Documents/Project2/Project2/";

void initialize(){
    A = (int*)malloc(sizeof(int)*LIST_SIZE);
    B = (int*)malloc(sizeof(int)*LIST_SIZE);
    C = (int*)malloc(sizeof(int)*LIST_SIZE);
    D = (int*)malloc(sizeof(int)*LIST_SIZE);
    E = (int*)malloc(sizeof(int)*LIST_SIZE);
    F = (int*)malloc(sizeof(int)*LIST_SIZE);
    G = (int*)malloc(sizeof(int)*LIST_SIZE);
    H = (int*)malloc(sizeof(int)*LIST_SIZE);
    I = (int*)malloc(sizeof(int)*LIST_SIZE);
    J = (int*)malloc(sizeof(int)*LIST_SIZE);
    K = (int*)malloc(sizeof(int)*LIST_SIZE);
    L = (int*)malloc(sizeof(int)*LIST_SIZE);
    M = (int*)malloc(sizeof(int)*LIST_SIZE);
    N = (int*)malloc(sizeof(int)*LIST_SIZE);
    O = (int*)malloc(sizeof(int)*LIST_SIZE);
    P = (int*)malloc(sizeof(int)*LIST_SIZE);
    Q = (int*)malloc(sizeof(int)*LIST_SIZE);
    R = (int*)malloc(sizeof(int)*LIST_SIZE);
    S = (int*)malloc(sizeof(int)*LIST_SIZE);
    T = (int*)malloc(sizeof(int)*LIST_SIZE);
    U = (int*)malloc(sizeof(int)*LIST_SIZE);
    V = (int*)malloc(sizeof(int)*LIST_SIZE);
    W = (int*)malloc(sizeof(int)*LIST_SIZE);
    X = (int*)malloc(sizeof(int)*LIST_SIZE);
    Y = (int*)malloc(sizeof(int)*LIST_SIZE);
    Z = (int*)malloc(sizeof(int)*LIST_SIZE);
    Blank = (int*)malloc(sizeof(int)*LIST_SIZE);
    
    for(int i = 0; i < LIST_SIZE; i++) {
        
        if(i%2 == 0){
            A[i] = 1;
            
        } else{
            
            A[i] = -1;
        }
    }
}




//void randomize(){}
void randomize(int * a, int n)
{
    int i = n - 1;
    int j, temp;
    srand(time(NULL));
    
    while (i > 0)
    {
        j = (rand()) % (i + 1);
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i = i - 1;
    }
}


size_t read_kernel(char* file_path){
    
    // Load the kernel source code into the array source_str
    FILE *fp;
    size_t source_size;
    
    fp = fopen(file_path, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    kernel_ptr = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( kernel_ptr, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
    
    return source_size; // this sould return file size
}
int ngram_count=0;
char ngram_tempchar[10];
int N_GRAM=0;

long read_source_file(char* file_path){
    long file_size;
    FILE *fpp = fopen(file_path, "r");
    if (fpp != NULL)
    {
        /* Go to the end of the file. */
        if (fseek(fpp, 0L, SEEK_END) == 0)
        {
            /* Get the size of the file. */
            long bufsize = ftell(fpp);  //current file position
            //printf("bufsize=%ld",bufsize);
            file_size = bufsize;
            if (bufsize == -1) { printf("Error-1");/* Error */ }
            
            /* Allocate our buffer to that size. */
            source_ptr = malloc(sizeof(char) * (bufsize + 1));
            
            /* Go back to the start of the file. */
            if (fseek(fpp, 0L, SEEK_SET) != 0)
            { printf("Error-2");/* Error */ }
            
            /* Read the entire file into memory. */
            //size_t newLen = fread(source_ptr, sizeof(char), bufsize, fpp);
            //printf("%zu \n",newLen);
            int i=0;
            while(!feof(fpp))
            {
                char ch = fgetc(fpp);
                ngram_count = 0;
                ngram_tempchar[10] = "\0";
                if(ch != 10 && ch != 13 && ch != '\0')
                {
                    source_ptr[i] += ch;
                    if(ch != 32) // if not space
                    {
                        ngram_tempchar[ngram_count] = ch;
                        ngram_count++;
                    }
                    else
                        N_GRAM = ngram_count;
                }
                i++;
                if ( ferror( fpp ) != 0 )  fputs("Error reading file", stderr);
                else source_ptr[i] = '\0'; /* Just to be safe. */
                source_ptr[i]='\0';
            }
            
        }
        fclose(fpp);
    }
    
    return file_size; // this sould return file size
}
//------------------------------------------------------------------------------------------------------------------------------

int* exe(char* file_path)
{
    
    size_t kernel_size = read_kernel("/Users/anoja/Documents/Project2/Project2/vector_add_kernel.cl");
    //size_t kernel_size = read_kernel("/Users/neelvekaria/Documents/OpenCL/sample4/sample4/vector_add_kernel.cl");
    N_GRAM=0;
    long file_size = read_source_file(file_path);
    char source_ptr2[(file_size - (N_GRAM-1) )*N_GRAM];
    int counter = 0;

    switch(N_GRAM)
    {
        case 1:
                for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
                {
                    if(source_ptr[n]!='\n')
                    {
                        source_ptr2[counter] = source_ptr[n];
                        counter++;
                    }
                }
                break;
        case 2:
                printf("Source ->\n");
                for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
                {
                    if(source_ptr[n]!='\n')
                    {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    }
                }
                break;
        case 3:
                printf("Source ->\n");
                for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
                {
                    if(source_ptr[n]!='\n')
                    {
                        source_ptr2[counter] = source_ptr[n];
                        counter++;
                        source_ptr2[counter] = source_ptr[n+1];
                        counter++;
                        source_ptr2[counter] = source_ptr[n+2];
                        counter++;
                    }
                }
            break;
        case 4:
            printf("Source ->\n");
            for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
            {
                if(source_ptr[n]!='\n')
                {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+2];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+3];
                    counter++;
                }
            }
            break;
        case 5:
            printf("Source ->\n");
            for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
            {
                if(source_ptr[n]!='\n')
                {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+2];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+3];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+4];
                    counter++;
                }
            }
            break;
        case 6:
            printf("Source ->\n");
            for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
            {
                if(source_ptr[n]!='\n')
                {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+2];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+3];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+4];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+5];
                    counter++;
                }
            }
            break;
        case 7:
            printf("Source ->\n");
            for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
            {
                if(source_ptr[n]!='\n')
                {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+2];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+3];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+4];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+5];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+6];
                    counter++;
                }
            }
            break;
        case 8:
            printf("Source ->\n");
            for (int n = 0; n < file_size - (N_GRAM-1) ; n++ )
            {
                if(source_ptr[n]!='\n')
                {
                    source_ptr2[counter] = source_ptr[n];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+1];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+2];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+3];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+4];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+5];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+6];
                    counter++;
                    source_ptr2[counter] = source_ptr[n+7];
                    counter++;

                }
            }
            break;
        default: break;

    }
    
    int *spt[(file_size - (N_GRAM-1) )*N_GRAM];
    
    for(int i=0; i< (file_size - (N_GRAM-1) )*N_GRAM; i++){
        //    printf("???%d??", spt[i]);
        
        switch(source_ptr2[i]){
                
            case 'a': spt[i]=  A;
                //printf("--%u--",spt[i]);
                break;
            case 'b': spt[i]= B  ;
                //printf("--%u--",spt[i]);
                break;
            case 'c': spt[i]= C  ;
                //printf("--%u--",spt[i]);
                break;
            case 'd': spt[i]= D  ;
                break;
            case 'e': spt[i]= E  ;
                break;
            case 'f': spt[i]= F  ;
                break;
            case 'g': spt[i]= G  ;
                break;
            case 'h': spt[i]= H  ;
                break;
            case 'i': spt[i]= I  ;
                break;
            case 'j': spt[i]= J  ;
                break;
            case 'k': spt[i]= K  ;
                break;
            case 'l': spt[i]= L  ;
                break;
            case 'm': spt[i]= M  ;
                break;
            case 'n': spt[i]= N  ;
                break;
            case 'o': spt[i]= O  ;
                break;
            case 'p': spt[i]= P  ;
                break;
            case 'q': spt[i]= Q  ;
                break;
            case 'r': spt[i]= R  ;
                break;
            case 's': spt[i]= S  ;
                break;
            case 't': spt[i]= T  ;
                break;
            case 'u': spt[i]= U  ;
                break;
            case 'v': spt[i]= V  ;
                break;
            case 'w': spt[i]= W  ;
                break;
            case 'x': spt[i]= X  ;
                break;
            case 'y': spt[i]= Y  ;
                break;
            case 'z': spt[i]= Z  ;
                break;
            case '\b': spt[i]= Blank ;
                break;
            default: spt[i]= 0;
                
        }
    }
    
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,
                   &device_id, &ret_num_devices);
    
    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    
    // Create memory buffers on the device for each vector
    cl_mem in0_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem in1_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem in2_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem out_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                        LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem temp_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         LIST_SIZE * sizeof(int), NULL, &ret);
    
    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,
                                                   (const char **)&kernel_ptr, (const size_t *)&kernel_size, &ret);
    
    // Build the program
    clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create the OpenCL kernel
    cl_kernel kernel = NULL;
    
    // Display the result to the screen
    //    long total=0;
    counter = 0;
    
    int *out = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *temp = (int*)malloc(sizeof(int)*LIST_SIZE);
    
    
    int *in0 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *in1 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *in2 = (int*)malloc(sizeof(int)*LIST_SIZE);
    
    
    for(int i=0;i<file_size-2;i++){
        //for(int i=0;i<(file_size - 2 );i++){
        for(int j=1;j<=3;j++){
            //    printf("\ngroup %d: %c -> %d\n",i, source_ptr2[counter], *in0);
            in0=spt[counter-2];
            in1=spt[counter-1];
            in2=spt[counter];
            counter++;
            
            clEnqueueWriteBuffer(command_queue, in0_mem_obj, CL_TRUE, 0,
                                 LIST_SIZE * sizeof(int), in0, 0, NULL, NULL);
            clEnqueueWriteBuffer(command_queue, in1_mem_obj, CL_TRUE, 0,
                                 LIST_SIZE * sizeof(int), in1, 0, NULL, NULL);
            clEnqueueWriteBuffer(command_queue, in2_mem_obj, CL_TRUE, 0,
                                 LIST_SIZE * sizeof(int), in2, 0, NULL, NULL);
        }
        
        kernel = clCreateKernel(program, "vector_add", &ret);
        
        clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&in0_mem_obj);
        clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&in1_mem_obj);
        clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&in2_mem_obj);
        clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&out_mem_obj);
        clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&temp_mem_obj);
        
        // Execute the OpenCL kernel on the list
        size_t global_item_size = LIST_SIZE; // Process the entire lists
        size_t local_item_size = 64; // Divide work items into groups of 64
        
        clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
                               &global_item_size, &local_item_size, 0, NULL, NULL);
        
        /*    // Read the memory buffer C on the device to the local variable C
         clEnqueueReadBuffer(command_queue, out_mem_obj, CL_TRUE, 0,
         LIST_SIZE * sizeof(int), out, 0, NULL, NULL);
         
         clEnqueueReadBuffer(command_queue, temp_mem_obj, CL_TRUE, 0,
         LIST_SIZE * sizeof(int), temp, 0, NULL, NULL);
         */
        
    }
    
    // Read the memory buffer C on the device to the local variable C
    clEnqueueReadBuffer(command_queue, out_mem_obj, CL_TRUE, 0,
                        LIST_SIZE * sizeof(int), out, 0, NULL, NULL);
    
    clEnqueueReadBuffer(command_queue, temp_mem_obj, CL_TRUE, 0,
                        LIST_SIZE * sizeof(int), temp, 0, NULL, NULL);
    for(int i=0; i< LIST_SIZE; i++){
        //printf("\nTemp Sum -> %d ", temp[i]);
        //printf("\nTotal Sum-> %d\n", out[i]);
        //  printf(".");
        
    }
    
    
    //   printf("\nFinal Sum -> %d\n", *out);
    
    // Clean up
    clFlush(command_queue);
    clFinish(command_queue);
    
    //  for(int i=0; i< file_size-2; i++){
    clReleaseKernel(kernel);
    //  }
    
    clReleaseProgram(program);
    clReleaseMemObject(in0_mem_obj);
    clReleaseMemObject(in1_mem_obj);
    clReleaseMemObject(in2_mem_obj);
    clReleaseMemObject(out_mem_obj);
    clReleaseMemObject(temp_mem_obj);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    
    return out;
    
    //free(in0);
    //free(in1);
    //free(in2);
    //free(out);
    //free(temp);
    
}

//--------------------------------------------------------------------------------------------------------------------------------

int dotProduct(int *in1, int *in2,int *in3, int *in4,int *in5, int *in6, int *in7, int *in8, int *testVector ){
    
    //    for(int i=0; i < 1000; i++) printf("\n In1 -->%d In2 -->%d TestVector -->%d ", in1[i],in2[i],testVector[i]);
    
    //    size_t kernel_size1 = read_kernel("/Users/neelvekaria/Documents/OpenCL/sample4/sample4/dotkernel.cl");
    
    
    // Read output memory buffer on the device to the local variable C
    
    double dot1=0 , dot2=0, dot3=0 , dot4=0 , dot5=0 , dot6=0 , dot7=0 , dot8=0 , out1=0, out2=0, out3=0 , out4=0 , out5=0 , out6=0, out7=0, out8=0, testVector2=0;
    /*
     int *dot1 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot2 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot3 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot4 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot5 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot6 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot7 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *dot8 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out1 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out2 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out3 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out4 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out5 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out6 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out7 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *out8 = (int*)malloc(sizeof(int)*LIST_SIZE);
     int *testVector2 =  (int*)malloc(sizeof(int)*LIST_SIZE);
     
     */
    
    for(int i =0; i<LIST_SIZE; i++){
        
        dot1 += in1[i] * testVector[i];
        dot2 += in2[i] * testVector[i];
        dot3 += in3[i] * testVector[i];
        dot4 += in4[i] * testVector[i];
        dot5 += in5[i] * testVector[i];
        dot6 += in6[i] * testVector[i];
        dot7 += in7[i] * testVector[i];
        dot8 += in8[i] * testVector[i];
        
        out1 += in1[i] * in1[i];
        out2 += in2[i] * in2[i];
        out3 += in3[i] * in3[i];
        out4 += in4[i] * in4[i];
        out5 += in5[i] * in5[i];
        out6 += in6[i] * in6[i];
        out7 += in7[i] * in7[i];
        out8 += in8[i] * in8[i];
        
        testVector2 += testVector[i] * testVector[i];
    }
    

    
    double static ans[8];
    double final=0;
    int num=0;
    
    printf("\ndot1 --> %f",dot1);
    //    printf("\ndot2 --> %d",dot2);
    printf("\nout1 --> %f",out1);
    //    printf("\nout2 --> %d",out2);
    printf("\ntestVector --> %f",testVector2);
    
    ans[0] = (double) dot1/(sqrt(out1) * sqrt(testVector2));
    ans[1] = dot2/(sqrt(out2) * sqrt(testVector2));
    ans[2] = dot3/(sqrt(out3) * sqrt(testVector2));
    ans[3] = dot4/(sqrt(out4) * sqrt(testVector2));
    ans[4] = dot5/(sqrt(out5) * sqrt(testVector2));
    ans[5] = dot6/(sqrt(out6) * sqrt(testVector2));
    ans[6] = dot7/(sqrt(out7) * sqrt(testVector2));
    ans[7] = dot8/(sqrt(out8) * sqrt(testVector2));
    
    for(int i =0; i<=7 ; i++){
        printf("\nans[%d] --> %f", i ,ans[i]);
    }
    
    final = ans[0];
    for(int i =0; i<8 ; i++){
        if(ans[i] > final)
        {
            final = ans[i];
            num = i;
        }
    }
    printf("\n\n final --> %f",final);
    printf("\n num --> %d",num);
    
    return num;
    
}


int main(void) {
    
    initialize();
    randomize(A,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) B[n]=A[n];
    randomize(B,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) C[n]=B[n];
    randomize(C,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) D[n]=C[n];
    randomize(D,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) E[n]=D[n];
    randomize(E,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) F[n]=E[n];
    randomize(F,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) G[n]=F[n];
    randomize(G,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) H[n]=G[n];
    randomize(H,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) I[n]=H[n];
    randomize(I,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) J[n]=I[n];
    randomize(J,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) K[n]=J[n];
    randomize(K,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) L[n]=K[n];
    randomize(L,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) M[n]=L[n];
    randomize(M,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) N[n]=M[n];
    randomize(N,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) O[n]=N[n];
    randomize(O,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) P[n]=O[n];
    randomize(P,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) Q[n]=P[n];
    randomize(Q,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) R[n]=Q[n];
    randomize(R,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) S[n]=R[n];
    randomize(S,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) T[n]=S[n];
    randomize(T,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) U[n]=T[n];
    randomize(U,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) V[n]=U[n];
    randomize(V,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) W[n]=V[n];
    randomize(W,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) X[n]=W[n];
    randomize(X,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) Y[n]=X[n];
    randomize(Y,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) Z[n]=Y[n];
    randomize(Z,LIST_SIZE);
    for (int n =0; n< LIST_SIZE ;n++  ) Blank[n]=Z[n];
    randomize(Blank,LIST_SIZE);
    
    
    //for (int n =0; n< LIST_SIZE ;n++  ) printf(" (A,B,C)= %d %d %d\n",A[n],B[n],C[n]);
    
    int *out0 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out1 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out2 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out3 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out4 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out5 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out6 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out7 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *out8 = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *testvector = (int*)malloc(sizeof(int)*LIST_SIZE);
    
    const char *train[8] = {"acq", "crude","earn", "grain", "interest","money-fx", "ship","trade" };
    const char *test[8] = {"acq", "crude","earn", "grain", "interest","money-fx", "ship","trade" };
    
    char *path= (char *) calloc(150,sizeof(char));
    
    for(int w=0; w<8; w++)
    {
        path[0] = '\0';
        strcat(path, "/Users/anoja/Documents/Project2/Project2/train1/");

       // strcat(path, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/train1/");
        strcat(path, train[w]);
        strcat(path, ".txt");
        printf("Loaded traning file %s \n", path);
        //   file_size = read_source_file(path);
        out0 = exe(path);
        switch (w) {
            case 0:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out1[i]=out0[i];
                }
                break;
            case 1:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out2[i]=out0[i];
                    //printf("\nfinal output in OUT2 --> %d", out2[i]);
                }
                break;
            case 2:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out3[i]=out0[i];
                }
                break;
            case 3:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out4[i]=out0[i];
                }
                break;
            case 4:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out5[i]=out0[i];
                }
                break;
            case 5:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out6[i]=out0[i];
                }
                break;
            case 6:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out7[i]=out0[i];
                }
                break;
            case 7:
                out0 = exe(path);
                for(int i=0;i<LIST_SIZE;i++){
                    out8[i]=out0[i];
                }
                break;
                /*
                 case 8:
                 out0 = exe(path);
                 for(int i=0;i<LIST_SIZE;i++){
                 testvector[i]=out0[i];
                 //printf("\nfinal output in OUT1 --> %d", out1[i]);
                 //printf("\nfinal output in OUT2 --> %d", out2[i]);
                 //printf("\nfinal output in OUT3 --> %d", out3[i]);
                 //printf("\nfinal output in OUT4 --> %d\n", out4[i]);
                 }
                 break;
                 */
            default:
                break;
        }
        
    }
    
    
    char *path1= (char *) calloc(150,sizeof(char));
    //    int *testvector1 = (int*)malloc(sizeof(int)*LIST_SIZE);
    char num[100];
    int counter=0;
    double accuracy=0;
    
    for(int w=0; w<8; w++)
    {
        switch (w){
            case 0:
                for(int i=0; i<696; i++)
                {
                    path1[0] = '\0';
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 1:
                for(int i=0; i<121; i++)
                {
                    path1[0] = '\0';
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 2:
                for(int i=0; i<1083; i++)
                {
                    path1[0] = '\0';
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
            case 3:
                for(int i=0; i<10; i++)
                {
                    path1[0] = '\0';
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 4:
                for(int i=0; i<81; i++)
                {
                    path1[0] = '\0';
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 5:
                for(int i=0; i<87; i++)
                {
                    path1[0] = '\0';
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 6:
                for(int i=0; i<36; i++)
                {
                    path1[0] = '\0';
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                    //strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            case 7:
                for(int i=0; i<75; i++)
                {
                    path1[0] = '\0';
                    strcat(path1, "/Users/anoja/Documents/Project2/Project2/test/");
                   // strcat(path1, "/Users/neelvekaria/Documents/OpenCL/sample4/sample4/test/");
                    strcat(path1, test[w]);
                    sprintf(num,"%d",i);
                    strcat(path1, num);
                    strcat(path1, ".txt");                      //print W
                    printf("\nLoaded testing file %s \n", path1);
                    //   file_size = read_source_file(path);
                    out0 = exe(path1);
                    
                    // out0 = exe(path1);
                    for(int i=0;i<LIST_SIZE;i++){
                        testvector[i]=out0[i];
                    }
                    double answer;
                    answer = dotProduct(out1, out2, out3, out4, out5, out6, out7, out8, testvector);
                    
                    if(answer == w)
                    {
                        counter++;
                    }
                }
                break;
            default:
                break;
                
                //  printf("----------------Testing-------------------");
                
        }
    }
    
    accuracy=(double)(counter/2201.0)*100.0;
    printf("\n\nFinal Accuracy ->%f\n",accuracy);
    
    free(A);
    free(B);
    free(C);
    free(D);
    free(E);
    free(F);
    free(G);
    free(H);
    free(I);
    free(J);
    free(K);
    free(L);
    free(M);
    free(N);
    free(O);
    free(P);
    free(Q);
    free(R);
    free(S);
    free(T);
    free(U);
    free(V);
    free(W);
    free(X);
    free(Y);
    free(Z);
    free(out1);
    free(out2);
    free(out3);
    free(out4);
    free(out5);
    free(out6);
    free(out7);
    free(out8);
    free(testvector);
    
    
}
