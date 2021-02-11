// DEMO by SpeedyZJF
/*.h files Demo Created by SpeedyZJF*/

#ifndef _ITKSTD_H_
#define _ITKSTD_H_

#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include <string>

// ----- Test -----//
#define MAJOR_VER 6
#define MINOR_VER 1
#define PATCH_VER 0
// ----- Test -----//

#define ITK_PTR_CREATE(type, name) type::Pointer name = type::New()

const unsigned int dim3 = 3;
const unsigned int dim2 = 2;

typedef unsigned char px8u;
typedef signed short px16s;
typedef float px32f;
typedef double px64f;

typedef itk::Image<px8u, dim3>								ImgType8u3d;
typedef itk::Image<px8u, dim2>								ImgType8u2d;
typedef itk::Image<px16s, dim3>								ImgType16s3d;
typedef itk::Image<px16s, dim2>								ImgType16s2d;
typedef itk::Image<px32f, dim3>								ImgType32f3d;
typedef itk::Image<px32f, dim2>								ImgType32f2d;
typedef itk::Image<px64f, dim3>								ImgType64f3d;
typedef itk::ImageRegionIterator <ImgType8u3d>	IterType8u3d;
typedef itk::ImageRegionIterator <ImgType16s3d>	IterType16s3d;
typedef itk::ImageRegionIterator <ImgType32f3d>	IterType32f3d;
typedef itk::ImageRegionIterator <ImgType64f3d>	IterType64f3d;

namespace demoAlgoItk {
		class className {
		public:
			className(char* arg);
			virtual ~className();
			int itkTestFunc();

			int lungSegDemo();
		protected:
			template<typename TImage> int writeMedicalMetaImage(
				typename TImage::Pointer inputImg, const std::string& nameStr);
		private:
			int m_Var = 0;
		
	};
}

#endif