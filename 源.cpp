#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define c1 1.49445 //加速度因子一般是根据大量实验所得
#define c2 1.49445
#define maxgen 30  // 迭代次数
#define sizepop 20 // 种群规模
#define popmax 2*1e22 // 个体最大取值
 #define popmin 1*1e11 // 个体最小取值
 #define Vmax 0.5*1e22 // 速度最大值
#define Vmin -0.5*1e11 //速度最小值
 #define dim 2 // 粒子的维数
 #define PI 3.1415926 //圆周率
double pop[sizepop][dim]; // 定义种群数组
 double V[sizepop][dim]; // 定义种群速度数组
 double fitness[sizepop]; // 定义种群的适应度数组
 double result[maxgen];  //定义存放每次迭代种群最优值的数组
 double pbest[sizepop][dim];  // 个体极值的位置
 double gbest[dim]; //群体极值的位置
 double fitnesspbest[sizepop]; //个体极值适应度的值
 double fitnessgbest; // 群体极值适应度值
 double genbest[maxgen][dim]; //每一代最优值取值粒子

 //适应度函数
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
	double x = *arr; //x 的值
	double y = *(arr + 1); //y的值
	double fitness = fabs(0.5*S21[k]-x*x/((x-4*PI*PI*T[k]*T[k])*(x - 4 * PI*PI*T[k] * T[k]) +y*y*4*PI*PI*T[k]*T[k]));
	return fitness;
	
		 }
 // 种群初始化
 void pop_init(void)
{
     for (int i = 0; i<sizepop; i++)
		     {
		       
		       
		            pop[i][0] = (((double)rand()) / RAND_MAX - 0.5) * 4*1e11; 
		             V[i][0] = ((double)rand()) / RAND_MAX - 0.5*1e11; 
					 pop[i][1] = (((double)rand()) / RAND_MAX - 0.5) * 4 * 1e22;
					 V[i][1] = ((double)rand()) / RAND_MAX - 0.5*1e22;
			        
		         fitness[i] = func(pop[i],i); //计算适应度函数值
		     }
	 }
 // min()函数定义
 double * min(double * fit, int size)
 {
	     int index = 0; // 初始化序号
	     double min = *fit; // 初始化最大值为数组第一个元素
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
 // 迭代寻优
 void PSO_func(void)
 {
	     pop_init();
	     double * best_fit_index; // 用于存放群体极值和其位置(序号)
	     best_fit_index = min(fitness, sizepop); //求群体极值
	     int index = (int)(*best_fit_index);
	     // 群体极值位置
		     for (int i = 0; i<dim; i++)
		     {
		         gbest[i] = pop[index][i];
		     }
	     // 个体极值位置
		     for (int i = 0; i<sizepop; i++)
		     {
		         for (int j = 0; j<dim; j++)
			         {
			             pbest[i][j] = pop[i][j];
			         }
		     }
	     // 个体极值适应度值
		     for (int i = 0; i<sizepop; i++)
		     {
	         fitnesspbest[i] = fitness[i];
	     }
	    //群体极值适应度值
		     double bestfitness = *(best_fit_index + 1);
	     fitnessgbest = bestfitness;
	
		     //迭代寻优
		     for (int i = 0; i<maxgen; i++)
		     {
		         for (int j = 0; j<sizepop; j++)
			         {
			             //速度更新及粒子更新
			             for (int k = 0; k<dim; k++)
				            {
			                 // 速度更新
					                 double rand1 = (double)rand() / RAND_MAX; //0到1之间的随机数
				                double rand2 = (double)rand() / RAND_MAX;
				                 V[j][k] = V[j][k] + c1*rand1*(pbest[j][k] - pop[j][k]) + c2*rand2*(gbest[k] - pop[j][k]);
				                 if (V[j][k] > Vmax)
					                    V[j][k] = Vmax;
				                 if (V[j][k] < Vmin)
					                     V[j][k] = Vmin;
				                 // 粒子更新
					                pop[j][k] = pop[j][k] + V[j][k];
				                 if (pop[j][k] > popmax)
					                    pop[j][k] = popmax;
				                if (pop[j][k] < popmin)
					                     pop[j][k] = popmin;
				            }
			            fitness[j] = func(pop[j],i); //新粒子的适应度值
			         }
		         for (int j = 0; j<sizepop; j++)
			         {
			             // 个体极值更新
				            if (fitness[j] > fitnesspbest[j])
				            {
				                 for (int k = 0; k<dim; k++)
					                 {
				                    pbest[j][k] = pop[j][k];
					                 }
				                 fitnesspbest[j] = fitness[j];
				             }
			            // 群体极值更新
				             if (fitness[j] > fitnessgbest)
				             {
				                 for (int k = 0; k<dim; k++)
					                     gbest[k] = pop[j][k];
				                 fitnessgbest = fitness[j];
				            }
			         }
		         for (int k = 0; k<dim; k++)
			         {
			             genbest[i][k] = gbest[k]; // 每一代最优值取值粒子位置记录
			         }
		         result[i] = fitnessgbest; // 每代的最优值记录到数组
		     }
	 }

 // 主函数
 int main(void)
 {
	     clock_t start, finish; //程序开始和结束时间
	     start = clock(); //开始计时
	     srand((unsigned)time(NULL)); // 初始化随机数种子
	     PSO_func();
	     double * best_arr;
	     best_arr = min(result, maxgen);
	     int best_gen_number = *best_arr; // 最优值所处的代数
	     double best = *(best_arr + 1); //最优值
	     printf("迭代了%d次，在第%d次取到最优值，最优值为:%lf.\n", maxgen, best_gen_number + 1, best);
	     printf("取到最优值的位置为(%lf,%lf).\n", genbest[best_gen_number][0], genbest[best_gen_number][1]);
	     finish = clock(); //结束时间
	     double duration = (double)(finish - start) / CLOCKS_PER_SEC; // 程序运行时间
	     printf("程序运行耗时:%lf\n", duration);
	     return 0;
	 }
