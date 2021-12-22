#include <stdio.h>
#include <stdlib.h>
#include <pwd.h> 

void myuser(const char *user) {
  struct passwd *buf;

  setpwent();
  if ((buf=getpwnam(user)) == NULL) {
    fprintf(stderr, "%s: unknown user\n", user);
    exit(1);
  }
  endpwent();

  printf("%s, %d, %d, %s,  %s, %s\n", buf->pw_name, buf->pw_uid, buf->pw_gid, buf->pw_gecos, buf->pw_dir, buf->pw_shell);

}

int main(int argc, char *argv[])
{
  myuser(argv[1]);

  return 0;
}

