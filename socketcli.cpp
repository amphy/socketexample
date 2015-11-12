#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;

#define MY_SOCK_PATH "socket.sock"
#define LISTEN_BACKLOG 50

void nope_out(string fname) {
  perror(fname.c_str());
  exit(EXIT_FAILURE);
} // nope_out

int main() {

  int cfd;
  string str;
  struct sockaddr_un my_addr;

  // create socket
  if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    nope_out("socket");
  } // if

  // duplicating the socket's fd into standard out
  // now, printing things goes to the socket
  dup2(cfd, STDOUT_FILENO);

  // clear and set structure
  memset(&my_addr, 0, sizeof(struct sockaddr_un));
  my_addr.sun_family = AF_UNIX;
  strcpy(my_addr.sun_path, MY_SOCK_PATH);

  // connect to the socket
  connect(cfd, (struct sockaddr *) &my_addr, sizeof(my_addr));

  cerr << "Dumping File..." << endl;
  while (true) {
	cin >> str;
	send(cfd, str.c_str(), strlen(str.c_str()), MSG_CONFIRM);
	//write(cfd, buffer, 1);
  } // while
  cerr << endl;

  return EXIT_SUCCESS;
} // main
