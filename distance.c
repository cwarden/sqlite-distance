#include <sqlite3ext.h>
#include <math.h>
#include <assert.h>
SQLITE_EXTENSION_INIT1

#define DEG2RAD(degrees) (degrees * 0.01745327) // degrees * pi over 180

static void distanceFunc(sqlite3_context *context, int argc, sqlite3_value **argv) {
	// check that we have four arguments (lat1, lon1, lat2, lon2)
	assert(argc == 4);
	// check that all four arguments are non-null
	if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL || sqlite3_value_type(argv[2]) == SQLITE_NULL || sqlite3_value_type(argv[3]) == SQLITE_NULL) {
		sqlite3_result_null(context);
		return;
	}
	// get the four argument values
	double lat1 = sqlite3_value_double(argv[0]);
	double lon1 = sqlite3_value_double(argv[1]);
	double lat2 = sqlite3_value_double(argv[2]);
	double lon2 = sqlite3_value_double(argv[3]);
	// convert lat1 and lat2 into radians now, to avoid doing it twice below
	double lat1rad = DEG2RAD(lat1);
	double lat2rad = DEG2RAD(lat2);
	// apply the spherical law of cosines to our latitudes and longitudes, and set the result appropriately
	// 6378.1 is the approximate radius of the earth in kilometres
	sqlite3_result_double(context, acos(sin(lat1rad) * sin(lat2rad) + cos(lat1rad) * cos(lat2rad) * cos(DEG2RAD(lon2) - DEG2RAD(lon1))) * 6378.1);
}

#ifdef _WIN32
__declspec(dllexport)
#endif
int sqlite3_distance_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg;  /* Unused parameter */
  rc = sqlite3_create_function(db, "distance", 4, SQLITE_UTF8, 0, distanceFunc, 0, 0);
  return rc;
}
