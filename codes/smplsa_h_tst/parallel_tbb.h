#ifndef PARALLEL_TBB_H
#define PARALLEL_TBB_H

#include "parameters.h"



class Parallel_Estep_pzwd:public cv::ParallelLoopBody{

	private:
		Mat *pwz,*pzd,*pzwd;
		int W,D,Z;

	public:
		Parallel_Estep_pzwd(Mat *pwz_in, Mat *pzd_in, Mat *pzwd_out): pwz(pwz_in), pzd(pzd_in), pzwd(pzwd_out){ 
			W=pzwd_out->size[0]; D=pzwd_out->size[1]; Z=pzwd_out->size[2];
		}

		virtual void operator()(const Range &w_range) const{
			double value, norm;
			for(int w=w_range.start;w<w_range.end;w++){
				for(int d=0;d<D;d++){
					norm=0.0;
					for(int z=0;z<Z;z++){
						value = pwz->at<double>(z,w) * pzd->at<double>(d,z);
						pzwd->at<double>(w,d,z) = value;
						norm += value;
					}
					if(norm!=0.0) 
						for(int z=0;z<Z;z++)
							pzwd->at<double>(w,d,z) /= norm;
				}
			}
		}
};



class Parallel_Mstep_pwz:public cv::ParallelLoopBody{

	private:
		Mat *pwd,*pzwd;
		double lambda;
		Mat *pwz;
		int W,D,Z;

	public:
		Parallel_Mstep_pwz(Mat *pwd_in, Mat *pzwd_in, double lambda_in, Mat *pwz_out): pwd(pwd_in), pzwd(pzwd_in), lambda(lambda_in), pwz(pwz_out){ 
			W=pzwd_in->size[0]; D=pzwd_in->size[1]; Z=pzwd_in->size[2];
		}

		virtual void operator()(const Range &z_range) const{
			double value, norm;
			for(int z=z_range.start;z<z_range.end;z++){
				norm=0.0;
				for(int w=0;w<W;w++){
					value=0.0;
					for(int d=0;d<D;d++){
						value += pwd->at<double>(d,w) * pzwd->at<double>(w,d,z);
					}
					// sparse regularisation //
					value -= lambda/W;
					if(value<0) value=0;
					///////////////////////////
					pwz->at<double>(z,w) = value;
					norm += value;
				}
				if(norm!=0.0) 
					for(int w=0;w<W;w++)
						pwz->at<double>(z,w) /= norm;
			}
		}
};



class Parallel_Mstep_pzd:public cv::ParallelLoopBody{

	private:
		Mat *pwd,*pzwd;
		double lambda;
		Mat *pzd;      
		int W,D,Z;

	public:
		Parallel_Mstep_pzd(Mat *pwd_in, Mat *pzwd_in, double lambda_in, Mat *pzd_out): pwd(pwd_in), pzwd(pzwd_in), lambda(lambda_in), pzd(pzd_out){ 
			W=pzwd_in->size[0]; D=pzwd_in->size[1]; Z=pzwd_in->size[2];
		}

		virtual void operator()(const Range &d_range) const{
			double value, norm;
			for(int d=d_range.start;d<d_range.end;d++){
				norm=0.0;
				for(int z=0;z<Z;z++){
					value=0.0;
					for(int w=0;w<W;w++){
						value += pwd->at<double>(d,w) * pzwd->at<double>(w,d,z);
					}
					// sparse regularisation //
					value -= lambda/Z;
					if(value<0) value=0;
					///////////////////////////
					pzd->at<double>(d,z) = value;
					norm += value;
				}
				if(norm!=0.0) 
					for(int z=0;z<Z;z++)
						pzd->at<double>(d,z) /= norm;
			}
		}
};



#endif