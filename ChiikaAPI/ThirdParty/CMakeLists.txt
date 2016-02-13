


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
add_subdirectory(pugixml/scripts)

#
#Modified Anitomy
#
add_subdirectory(anitomy)

add_boost_library(system)
add_boost_library(filesystem)
add_boost_library(date_time)
add_boost_library(regex)
add_boost_library(thread)

set_target_properties(boost_system PROPERTIES FOLDER "3rdParty" )
set_target_properties(boost_filesystem PROPERTIES FOLDER "3rdParty" )
set_target_properties(boost_thread PROPERTIES FOLDER "3rdParty" )
set_target_properties(boost_date_time PROPERTIES FOLDER "3rdParty" )
set_target_properties(boost_regex PROPERTIES FOLDER "3rdParty" )





#
#log4cplus
#
add_subdirectory(log4cplus)
