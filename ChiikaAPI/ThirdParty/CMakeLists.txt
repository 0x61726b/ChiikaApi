


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

if(OS_LINUX)
  target_compile_options(boost_system PUBLIC "-fPIC")
  target_compile_options(boost_filesystem PUBLIC "-fPIC")
  target_compile_options(boost_thread PUBLIC "-fPIC")
  target_compile_options(boost_date_time PUBLIC "-fPIC")
  target_compile_options(boost_regex PUBLIC "-fPIC")
endif()



#
#log4cplus
#
add_subdirectory(log4cplus)
