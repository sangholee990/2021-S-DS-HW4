#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //행렬을 생성하는 함수 선언 
void print_matrix(int** matrix, int row, int col); //행렬 출력 함수 선언 
int free_matrix(int** matrix, int row, int col);// 동적할당된 배열 해제 하는 함수 선언 
int fill_data(int** matrix, int row, int col);// 행렬에 다시 값 넣는 함수 선언 
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬 덧셈 함수 선언 
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬 뺄셈 함수 선언 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);//전치 행렬 계산 함수 선언 
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);//행렬 곱셉 함수 선언 

int main()
{

    char command; // 사용자에게 명령 받는 변수  
    printf("[----- [이상호]  [2018038016] -----]\n"); // 이름 학번 출력 

    int row, col; // 행,열 받는 변수 
    srand(time(NULL)); // 현재시각을 초단위로 반환하여 난수 생성  

    printf("Input row and col : "); //행렬의 사이즈 입력 요구 출력
    scanf("%d %d", &row, &col); // 행렬의 사이즈 사용자로 부터 입력 받기
    int** matrix_a = create_matrix(row, col); //행렬 a 생성
    int** matrix_b = create_matrix(row, col); // 행렬 b 생성
    int** matrix_a_t = create_matrix(col, row); // 행렬 a의 전치 행렬 생성

    printf("Matrix Created.\n"); // 행렬이 생성 되었음을 출력 

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} // 행렬 배열에 값이 비어있으면 -1 반환  

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n"); //메뉴 출력 

        printf("Command = "); 
        scanf(" %c", &command); // 사용자에게 명령 받기  

        switch(command) {
        case 'z': case 'Z': // 사용자가 Z를 입력했을 경우  
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col); // 첫번째 행렬 초기화 
            fill_data(matrix_b, row, col); // 두번째 행렬 초기화 
            break;
        case 'p': case 'P':// 사용자가 P를 입력했을 경우  
            printf("Print matrix\n"); 
            printf("matrix_a\n"); 
            print_matrix(matrix_a, row, col); //첫번째 행렬 출력 
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //두번째 행렬 출력  
            break;
        case 'a': case 'A':// 사용자가 A를 입력했을 경우  
            printf("Add two matrices\n"); 
            addition_matrix(matrix_a, matrix_b, row, col); // 첫번째 행렬과 두번째 행렬을 더한 행렬을 출력 
            break;
        case 's': case 'S':// 사용자가 S를 입력했을 경우  
            printf("Subtract two matrices \n");  
            subtraction_matrix(matrix_a, matrix_b, row, col); // 첫번째 행렬에서 두번째 행렬을 뺀 행렬을 출력 
            break;
        case 't': case 'T':// 사용자가 T를 입력했을 경우  
            printf("Transpose matrix_a \n"); // 
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 첫번째 행렬의 전치행렬을 계산 
            print_matrix(matrix_a_t, col, row); // 전치행렬 출력 
            break;
        case 'm': case 'M':// 사용자가 M를 입력했을 경우  
            printf("Multiply matrix_a with transposed matrix_a \n"); 
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 첫번째 행렬의 전치행렬을 계산 
            multiply_matrix(matrix_a, matrix_a_t, row, col); // 첫번째 행렬과 그 전치행렬을 곱한 행렬을 출력  
            break;
        case 'q': case 'Q':// 사용자가 Q를 입력했을 경우  
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //첫번째 행렬의 전치 행렬 동적 할당 해제 
            free_matrix(matrix_a, row, col);// 첫번째 행렬의 동적 할당 해제 
            free_matrix(matrix_b, row, col);// 두번째 행렬의 동적 할당 해제 
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); // 사용자가 Q를 입력할때 까지 반복 

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	      
            if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 

	       int i; //반복문 용 변수 i
		   int k; //반복문 용 변수 K; 
	       int** matrix=(int**)malloc(sizeof(int*)*row); //행 사이즈 만큼 동적 할당 
           for(i=0;i<row;i++){ //행 만큼 반복 
        	   matrix[i]=(int**)malloc(sizeof(int*)*col); //열 사이즈 만큼 동적 할당  
           }
           for(i=0;i<row;i++){
           	   for(k=0;k<col;k++){
           	   	   matrix[i][k]=rand()%20; // 행렬배열에 0~19까지의 난수 설정 
				  }
		   }
           return matrix; // 설정된 배열 리턴  
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	    if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
             int i,k; //반복문용 변수 i,k 선언 
			 for(i=0;i<row;i++){
			 	for(k=0;k<col;k++){
			 		printf("%d",matrix[i][k]); // row, col 사이즈의 행렬 값 출력  
			 		printf("\t");
				 }
			    printf("\n");
			 }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	    if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
             int i; //반복문 용 변수 i 
           
             for(i=0;i<col;i++){
             		free(matrix[i]); //열 공간 동적 할당 해제 
			 }
			 
			 free(matrix);//행 공간 동적 할당해제  
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	   if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
        int i; //반복문 용 변수 i  
        int k; // 반복문 용 변수 k 
            for(i=0;i<row;i++){
           	   for(k=0;k<col;k++){
           	   	   matrix[i][k]=rand()%20; //row col 사이즈 행렬에 난수 설정  
				  }
		   }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
	   if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
        int i; //반복문 용 변수 i 
        int k; //반복문 용 변수 k 
        
        int matrix[row][col]; //row col 사이즈 배열 생성 
           
        for(i=0;i<row;i++){
        	for(k=0;k<col;k++){
        		matrix[i][k]=matrix_a[i][k]+matrix_b[i][k]; //행렬 덧셈 알고리즘  
			}
		}

		for(i=0;i<row;i++){
        	for(k=0;k<col;k++){
        		printf("%d",matrix[i][k]); //덧셈 완료된 행렬 출력  
        		printf("\t");
			}
			printf("\n");
		}
		

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{ 
        if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
        int i; // 반복문 용 변수 i 
        int k; // 반복문 용 변수 k 
        
        int matrix[row][col]; //row col 사이즈 배열 생성
           
        for(i=0;i<row;i++){
        	for(k=0;k<col;k++){
        		matrix[i][k]=matrix_a[i][k]-matrix_b[i][k]; //행렬 뺄셈 알고리즘  
			}
		}

		for(i=0;i<row;i++){
        	for(k=0;k<col;k++){
        		printf("%d",matrix[i][k]); //뺄셈 완료된 행렬 출력  
        		printf("\t");
			}
			printf("\n");
		}
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	    if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
        int i,k,j; // 반복문 용 변수 ikj  

        for(i=0;i<row;i++){
        	for(k=0;k<col;k++){
        		matrix_t[i][k]=matrix[k][i]; //martix에 행과 열을 바꿔서 matrix_t 에 저장  
			}
		}

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
	    if(row <= 0 || col <=0) {
               printf("Check the sizes of row and col!\n");
               return NULL;} // 비정상값 입력시 안내문 출력후 종료 
               
	    int i,k,j; // 반복문 용 변수 ikj 
	    
	    int matrix[row][col]; //row col 사이즈 배열 생성
           
	    int sum=0; // 행렬 곱의 합  저장 변수 sum 선언  

	    for(i=0;i<row;i++){
	    	for(k=0;k<row;k++){ // row * row 인 이유는 row * col 행렬의 경우 전치행렬의 크기가 col * row 이므로 행렬* 전치행렬의 크기는 row * row 가된다. 
	    		sum=0; //sum 값 초기화 
	    		for(j=0;j<col;j++){
	    			sum+=matrix_a[i][j]*matrix_t[j][k]; // 행렬 한개 성분의 계산값 저장  
				}
			matrix[i][k]=sum; // 계산된 값 matrix에 저장  
			}
		}

		for(i=0;i<row;i++){
			for(k=0;k<row;k++){
				printf("%d",matrix[i][k]); // 행렬*전치행렬 출력  
				printf("\t");
			}
			printf("\n");
		}
}

