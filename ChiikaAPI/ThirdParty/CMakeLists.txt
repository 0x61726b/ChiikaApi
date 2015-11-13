


#
#Curl
#
#add_subdirectory(curl)
#To not override compiler flags for curl we dont add it here


#
#JsonCpp
#
add_subdirectory(jsoncpp)

#
#PugiXML
#
add_subdirectory(pugixml\\scripts)

#
#Modified Anitomy
#
add_subdirectory(anitomy)

#
#
#To-do add build test 
if(IncludeGoogleMock)
	add_subdirectory(googletest\\googlemock)
endif()	

