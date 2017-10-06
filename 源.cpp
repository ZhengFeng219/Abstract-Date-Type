#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define c1 1.49445 //���ٶ�����һ���Ǹ��ݴ���ʵ������
#define c2 1.49445
#define maxgen 30  // ��������
#define sizepop 20 // ��Ⱥ��ģ
#define popmax 2*1e22 // �������ȡֵ
 #define popmin 1*1e11 // ������Сȡֵ
 #define Vmax 0.5*1e22 // �ٶ����ֵ
#define Vmin -0.5*1e11 //�ٶ���Сֵ
 #define dim 2 // ���ӵ�ά��
 #define PI 3.1415926 //Բ����
double pop[sizepop][dim]; // ������Ⱥ����
 double V[sizepop][dim]; // ������Ⱥ�ٶ�����
 double fitness[sizepop]; // ������Ⱥ����Ӧ������
 double result[maxgen];  //������ÿ�ε�����Ⱥ����ֵ������
 double pbest[sizepop][dim];  // ���弫ֵ��λ��
 double gbest[dim]; //Ⱥ�弫ֵ��λ��
 double fitnesspbest[sizepop]; //���弫ֵ��Ӧ�ȵ�ֵ
 double fitnessgbest; // Ⱥ�弫ֵ��Ӧ��ֵ
 double genbest[maxgen][dim]; //ÿһ������ֵȡֵ����

 //��Ӧ�Ⱥ���
 double func(double * arr,int n)
 {
	double S21[30] = { 0.293393782,0.293580025,0.293708489,0.293779176,0.293792084,0.293747213,0.293644565,0.293484138,0.293265933
	,0.292989949,0.292656188,0.292264648,0.29181533,0.291308234,0.290743359,0.290120706,0.289440275,0.288702066,0.287906078
	,0.287052312,0.286140768,0.285171446,0.284144345,0.283059467,0.28191681,0.280716374,0.279458161,0.278142169,0.276768399
	,0.27533685};
	double T[30] = {0,10000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000,100000000,110000000,120000000,
		130000000,140000000,150000000,160000000,170000000,180000000,190000000,200000000,210000000,220000000,230000000,240000000
,250000000,260000000,270000000,280000000,290000000};
	int k = n;
	double x = *arr; //x ��ֵ
	double y = *(arr + 1); //y��ֵ
	double fitness = fabs(0.5*S21[k]-x*x/((x-4*PI*PI*T[k]*T[k])*(x - 4 * PI*PI*T[k] * T[k]) +y*y*4*PI*PI*T[k]*T[k]));
	return fitness;
	
		 }
 // ��Ⱥ��ʼ��
 void pop_init(void)
{
     for (int i = 0; i<sizepop; i++)
		     {
		       
		       
		            pop[i][0] = (((double)rand()) / RAND_MAX - 0.5) * 4*1e11; 
		             V[i][0] = ((double)rand()) / RAND_MAX - 0.5*1e11; 
					 pop[i][1] = (((double)rand()) / RAND_MAX - 0.5) * 4 * 1e22;
					 V[i][1] = ((double)rand()) / RAND_MAX - 0.5*1e22;
			        
		         fitness[i] = func(pop[i],i); //������Ӧ�Ⱥ���ֵ
		     }
	 }
 // min()��������
 double * min(double * fit, int size)
 {
	     int index = 0; // ��ʼ�����
	     double min = *fit; // ��ʼ�����ֵΪ�����һ��Ԫ��
	     static double best_fit_index[2];
	     for (int i = 1; i<size; i++)
		     {
		         if (*(fit + i) < min)
			             min = *(fit + i);
		             index = i;
		    }
	     best_fit_index[0] = index;
	     best_fit_index[1] = min;
	     return best_fit_index;
			 }
 // ����Ѱ��
 void PSO_func(void)
 {
	     pop_init();
	     double * best_fit_index; // ���ڴ��Ⱥ�弫ֵ����λ��(���)
	     best_fit_index = min(fitness, sizepop); //��Ⱥ�弫ֵ
	     int index = (int)(*best_fit_index);
	     // Ⱥ�弫ֵλ��
		     for (int i = 0; i<dim; i++)
		     {
		         gbest[i] = pop[index][i];
		     }
	     // ���弫ֵλ��
		     for (int i = 0; i<sizepop; i++)
		     {
		         for (int j = 0; j<dim; j++)
			         {
			             pbest[i][j] = pop[i][j];
			         }
		     }
	     // ���弫ֵ��Ӧ��ֵ
		     for (int i = 0; i<sizepop; i++)
		     {
	         fitnesspbest[i] = fitness[i];
	     }
	    //Ⱥ�弫ֵ��Ӧ��ֵ
		     double bestfitness = *(best_fit_index + 1);
	     fitnessgbest = bestfitness;
	
		     //����Ѱ��
		     for (int i = 0; i<maxgen; i++)
		     {
		         for (int j = 0; j<sizepop; j++)
			         {
			             //�ٶȸ��¼����Ӹ���
			             for (int k = 0; k<dim; k++)
				            {
			                 // �ٶȸ���
					                 double rand1 = (double)rand() / RAND_MAX; //0��1֮��������
				                double rand2 = (double)rand() / RAND_MAX;
				                 V[j][k] = V[j][k] + c1*rand1*(pbest[j][k] - pop[j][k]) + c2*rand2*(gbest[k] - pop[j][k]);
				                 if (V[j][k] > Vmax)
					                    V[j][k] = Vmax;
				                 if (V[j][k] < Vmin)
					                     V[j][k] = Vmin;
				                 // ���Ӹ���
					                pop[j][k] = pop[j][k] + V[j][k];
				                 if (pop[j][k] > popmax)
					                    pop[j][k] = popmax;
				                if (pop[j][k] < popmin)
					                     pop[j][k] = popmin;
				            }
			            fitness[j] = func(pop[j],i); //�����ӵ���Ӧ��ֵ
			         }
		         for (int j = 0; j<sizepop; j++)
			         {
			             // ���弫ֵ����
				            if (fitness[j] > fitnesspbest[j])
				            {
				                 for (int k = 0; k<dim; k++)
					                 {
				                    pbest[j][k] = pop[j][k];
					                 }
				                 fitnesspbest[j] = fitness[j];
				             }
			            // Ⱥ�弫ֵ����
				             if (fitness[j] > fitnessgbest)
				             {
				                 for (int k = 0; k<dim; k++)
					                     gbest[k] = pop[j][k];
				                 fitnessgbest = fitness[j];
				            }
			         }
		         for (int k = 0; k<dim; k++)
			         {
			             genbest[i][k] = gbest[k]; // ÿһ������ֵȡֵ����λ�ü�¼
			         }
		         result[i] = fitnessgbest; // ÿ��������ֵ��¼������
		     }
	 }

 // ������
 int main(void)
 {
	     clock_t start, finish; //����ʼ�ͽ���ʱ��
	     start = clock(); //��ʼ��ʱ
	     srand((unsigned)time(NULL)); // ��ʼ�����������
	     PSO_func();
	     double * best_arr;
	     best_arr = min(result, maxgen);
	     int best_gen_number = *best_arr; // ����ֵ�����Ĵ���
	     double best = *(best_arr + 1); //����ֵ
	     printf("������%d�Σ��ڵ�%d��ȡ������ֵ������ֵΪ:%lf.\n", maxgen, best_gen_number + 1, best);
	     printf("ȡ������ֵ��λ��Ϊ(%lf,%lf).\n", genbest[best_gen_number][0], genbest[best_gen_number][1]);
	     finish = clock(); //����ʱ��
	     double duration = (double)(finish - start) / CLOCKS_PER_SEC; // ��������ʱ��
	     printf("�������к�ʱ:%lf\n", duration);
	     return 0;
	 }
