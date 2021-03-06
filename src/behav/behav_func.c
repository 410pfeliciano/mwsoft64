#include "behav_ext.h"

/*
*************************************
**            FUNCTIONS            **
*************************************
*/

int32_t datacompare(s1,s2)
SpikeData	*s1,*s2;
{
    return(s1->timestamp - s2->timestamp);
}

int32_t positioncompare(p1,p2)
Position	*p1,*p2;
{
    return(p1->timestamp - p2->timestamp);
}

void ResetVectors(result)
Result	*result;
{
int32_t	i;

    if(result->savemode == VECTOR){
	bzero(result->vector,sizeof(float)*MAXTHETA);
	bzero(result->vectorn,sizeof(int32_t)*MAXTHETA);
	bzero(result->vectortotaln,sizeof(int32_t)*MAXTHETA);
	bzero(result->vectorsumsqr,sizeof(float)*MAXTHETA);
    } else {
	for(i=0;i<result->xsize;i++){
	    bzero(result->grid[i],sizeof(float)*result->ysize);
	    bzero(result->gridn[i],sizeof(int32_t)*result->ysize);
	    bzero(result->gridtotaln[i],sizeof(int32_t)*result->ysize);
	    bzero(result->gridsumsqr[i],sizeof(float)*result->ysize);
	}
    }
}

void ComputeCoordinates(px,py,result,x,y)
int32_t	px;
int32_t	py;
Result	*result;
int32_t	*x;
int32_t	*y;
{
float 	val;
float	xval;
float	yval;
float	theta;

    xval = px;
    yval = py;
    /*
    ** perform rotation.
    ** first translate to the origin 
    */
    theta = result->rotation*2*M_PI/360.0;
    xval = (px - result->xres/2)*cos(theta) - 
	(py - result->yres/2)*sin(theta);
    yval = (px - result->xres/2)*sin(theta) + 
	(py - result->yres/2)*cos(theta);
    /*
    ** then translate back
    */
    xval += result->xres/2;
    yval += result->yres/2;
    /*
    ** add translations
    */
    val = ((float)xval-result->xoffset)*(result->xsize/result->xres);
    if(val < 0){
	/*
	** truncate down for negative numbers
	*/
	*x = val - 1;
    } else {
	*x = val;
    }
    val = ((float)yval-result->yoffset)*(result->ysize/result->yres);
    if(val < 0){
	/*
	** truncate down for negative numbers
	*/
	*y = val - 1;
    } else {
	*y = val;
    }
}

