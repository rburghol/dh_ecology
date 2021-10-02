library("hydrotools")
library("httr")

basepath = "/var/www/R"
source(paste(basepath,"config.R", sep="/"))

ds <- RomDataSource$new("http://www.grapeipm.org/d.live", rest_w_uname)
ds$get_token(rest_w_pass)

# not yet working.  Need to congiure entity properly for rest
#   EntityMetadataWrapperException: Invalid data value given. 
#   Be sure it matches the required data type and format. in 
#   EntityDrupalWrapper->set() (line 736 of 
#   /var/www/d.live/modules/entity/includes/entity.wrapper.inc).
dhw <- ds$get(
  'dh_ecology_isolate', 
  'iid', 
  list(iid = 498)
)


