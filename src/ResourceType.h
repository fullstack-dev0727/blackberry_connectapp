#ifndef RESOURCETYPE_H
#define RESOURCETYPE_H

    ///Doing like that because BB doesn't support C++0x and enum doesn't have a namespace...
	class ResourceType
	{
	public :
	        static const int Locality = 1;
            static const int Subdivision = 2;
            static const int Household = 3;
            static const int Interchange = 4;
            static const int CurrentUser = 5;
            static const int Country = 6;
            static const int CountryAll = 7;
	};
#endif

