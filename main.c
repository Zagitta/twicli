#include<stdio.h>
#include<roxml.h>
#include<http_fetcher.h>

const char *streamListUrl = "http://api.justin.tv/api/stream/list.xml?limit=%d&category=gaming"; 

int main(int argc, char **argv)
{
  int limit = 10;
  char formattedUrl[1000];

  if(argc > 1)
  {
    limit = atoi(argv[1]);
  }

  sprintf(formattedUrl, streamListUrl, limit); 

  //printf("fetching: %s\n", formattedUrl);

  char *data = NULL;

  int downloaded = http_fetch(formattedUrl, &data);

  //printf("downloaded %d bytes\n", downloaded);

  if(downloaded < 1)
  {
    printf("error in download, exiting");
    return 0;
  }

  node_t *xml = roxml_load_buf(data);

  int streamCount = roxml_get_chld_nb(xml);

  if(streamCount == 0)
  {
    printf("No streams were found!");
    return 0;
  }

  xml = roxml_get_chld(xml, NULL, 0);

  //get first stream
  node_t *child = roxml_get_chld(xml, NULL, 0);

  do
  {
    node_t *channelXml = roxml_get_chld(child, "channel", 0);
    node_t *channelUrlXml = roxml_get_txt(roxml_get_chld(channelXml, "login", 0),0);
    
    node_t *titleXml = roxml_get_txt(roxml_get_chld(child, "title", 0), 0);

    int len = 0;
    printf("%-20s%s\n",
	   roxml_get_content(channelUrlXml, NULL, 0, &len),
	   roxml_get_content(titleXml, NULL, 0, &len));
  }
  while(child = roxml_get_next_sibling(child));
  
  return 0;
}
