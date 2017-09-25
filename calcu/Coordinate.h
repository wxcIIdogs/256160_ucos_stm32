#ifndef __COORDINATE_H
#define __COORDINATE_H
#include "common.h"
#include "math.h"

#define RE_WGS84    6378137.0           /* earth semimajor axis (WGS84) (m) */
#define FE_WGS84    (1.0/298.257223563) /* earth flattening (WGS84) */
#define PI          3.1415926535897932  /* pi */
#define D2R         (PI/180.0)          /* deg to rad */
#define R2D         (180.0/PI)          /* rad to deg */

extern void ecef2pos(const double *r, double *pos);
extern void pos2ecef(const double *pos, double *r);
extern void xyz2enu(const double *pos, double *E);
extern void ecef2enu(const double *pos, const double *r, double *e);
extern void enu2ecef(const double *pos, const double *e, double *r);

#endif /* __COORDINATE_H */
