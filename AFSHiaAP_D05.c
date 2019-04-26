#define FUSE_USE_VERSION 28
#define HAVE_SETXATTR

#include <pwd.h>
#include <grp.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

const int en_key = 17;
int de_key = -17;
char *cipher = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
char newstring[100] = "";

char* caesar(char input[100], int key)
{
	strcpy(newstring, input);
	int panjangcipher = strlen(cipher);
	int panjanginput = strlen(input);
	int x;
	int y;
	for(x = 0; x < panjanginput; x++)
	{
		for(y = 0; y < panjangcipher; y++)
		{
			if(input[x] == cipher[y])
			{
				int shift;
				shift = y + key;
				if(shift < 0)
				{
					shift = panjangcipher + shift;
				}
				newstring[x] = cipher[(shift)%(panjangcipher)];
			}
		}
	}

	return newstring;
}

//////////////
// struct stat info;
//             stat(dir->d_name, &info);
//             char ex000[1000],string[1000],sub[1000],flname[1000], tujuan[1000];
//             int c=0;
//             strcpy(string,dir->d_name);
//             int len = strlen(string);
//             int ext = len-4;
//             // printf("%d",len);
//             while (c < 2 && len > 8) {
//                 sub[c] = string[ext+c];
//                 c++;
//             }
//             sub[c] = '\0';
//             c = 0;
//             int st = len-3;
//             while (c < 3 && len > 8) {
//                 ex000[c] = string[st+c];
//                 c++;
//             }
//             ex000[c] = '\0';
//             // printf("%s", ex000);
//             c=0;
//             while (c < len-4 && len > 8) {
//                 flname[c] = string[c];
//                 c++;
//             }
//             flname[c] = '\0';
//             // printf("%s\n", sub);
//             if (strcmp(sub,".0")==0){
                
//                 FILE * fp, * fs;
//                 fs = fopen(string, "r");
//                 // if (strcmp(ex000,"000") == 0) remove(flname);
//                 fp = fopen (flname, "a+");
//                 char ch;
//                 while((ch = fgetc(fs)) != EOF) fputc(ch,fp);
//                 fclose(fp); 
//                 fclose(fs); 
//                 sprintf(tujuan,"Videos/%s",string);
//                 rename(string, tujuan);
//             }
            

///////////
static const char *dirpath = "/home/yusuf/shift4";
//int create_file = 0;

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  	int res;
	char fpath[1000];
	char pathmodified[100];
	sprintf(pathmodified, "%s", path);
	strcpy(pathmodified, caesar(pathmodified, en_key));
	sprintf(fpath,"%s%s",dirpath,pathmodified);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n%s\n\n\n\n\n\n", fpath);

	/*
	if(create_file == 1)
	{
		char* ext = "`[S%";
		sprintf(fpath, "%s%s", fpath, ext);
		create_file = 0;
	}
	*/
	res = lstat(fpath, stbuf);
	memset(pathmodified, 0, sizeof(pathmodified));
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char newpath[100] = "";
		strcpy(newpath, path);
		strcpy(newpath, caesar(newpath, en_key));
 		sprintf(fpath, "%s%s",dirpath,newpath);
	}
    
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
        ///////////////////
		struct stat st;
        struct stat info;
        stat(de->d_name, &info);
        int result = access(de->d_name, R_OK); 
        struct passwd *pw = getpwuid(info.st_uid);
        struct group  *gr = getgrgid(info.st_gid);
        if ( ( strcmp(pw->pw_name , "chipset") == 0 || strcmp(pw->pw_name, "ic_controller") == 0)){
            if ( strcmp(gr->gr_name, "rusak"))
            {
                if (result == -1)
                {
                    FILE * fp;
                    fp = fopen ("/home/yusuf/shift4/filemiris.txt", "a");
                    fprintf(fp, "%s : %s : %s : %s\n",de->d_name, gr->gr_name, pw->pw_name,ctime(&info.st_atime));
                    fclose(fp);
                    remove(de->d_name);
                }
            }
            
        }
        //////////////////
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		//printf("%s\n", de->d_name);
		char convertstring[100];
		memset(convertstring, 0, sizeof(convertstring));
		strcpy(convertstring, de->d_name);
		strcpy(convertstring, caesar(convertstring, de_key));
		if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0)
		{
			res = (filler(buf, convertstring, &st, 0));
		}
		else
		{
			res = (filler(buf, de->d_name, &st, 0));
		}
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	//mode_t fixedmode = 750;
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s", path);
	}
	else
	{
		char newpath[100] = "";
		strcpy(newpath, path);
		strcpy(newpath, caesar(newpath, en_key));
		sprintf(fpath,"%s%s",dirpath,newpath);
	}
	int res;
	char* check = strstr(fpath, "@ZA>AXio");
	//printf("%s\n", check);
	if(check != NULL)
	{
		res = mkdir(fpath, 0750);
		//chmod(fpath, fixedmode);
	}
	else
	{
		res = mkdir(fpath, mode);
		//chmod(fpath, mode);
	}
	if(res == -1)
		return -errno;

	return 0;
}

//char testing[100] = "";

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi)
{
	(void) fi;

	//mode_t fixedmode = 640;
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path = dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char newpath[100] = "";
		strcpy(newpath, path);
		strcpy(newpath, caesar(newpath, en_key));
		sprintf(fpath,"%s%s", dirpath, newpath);
	}
	int res;
	//YOUTUBER
	char* check = strstr(fpath, "@ZA>AXio");
	//strcpy(testing, check);
	//printf("%s\n", testing);
	if(check != NULL)
	{
		char* ext = "`[S%";
		res = creat(fpath, 0640);
		char newpath[100] = "";

		pid_t child = fork();
		if(child == 0)
		{
			sprintf(newpath,"%s%s",fpath,ext);
			char* argv[] = {"mv", fpath, newpath, NULL};
			execv("/bin/mv", argv);
			//rename(fpath, newpath);

		}
		//create_file = 1;
		//chmod(fpath, fixedmode);
	}
	else
	{
		res = creat(fpath, mode);
		//chmod(fpath, mode);
	}
	if(res == -1)
		return -errno;

	close(res);

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path = dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char newpath[100] = "";
		strcpy(newpath, path);
		strcpy(newpath, caesar(newpath, en_key));
		sprintf(fpath,"%s%s",dirpath,newpath);
	}
	int res;

	printf("\n\n\n\n\n%s\n\n\n\n", fpath);
	//Extension
	char target[100];
	strcpy(target, fpath);

	int length = strlen(target);
	char ext[4] = "`[S%";

	//char *argv[] = ("echo", target, NULL);
	//execv("/bin/echo", argv);

	int marker = 0;
	int x;
	for(x = 0; x < 4; x++)
	{
		if(ext[x] == target[length - 4 + x])
		{
			marker++;
		}
	}

	if(marker != 4)
	{
		res = chmod(fpath, mode);
	}
	else
	{
		pid_t child = fork();
		if(child == 0)
		{
		char *argv[] = {"zenity", "--error", "--text='File ekstensi iz1 tidak boleh diubah permissionnya'", NULL};
		execv("/usr/bin/zenity", argv);
		}
	}

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path = dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char newpath[100] = "";
		strcpy(newpath, path);
		strcpy(newpath, caesar(newpath, en_key));
		sprintf(fpath,"%s%s",dirpath,newpath);
	}
	int res;

	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;
	struct timeval tv[2];

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(path, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.mkdir		= xmp_mkdir,
	.create		= xmp_create,
	.chmod		= xmp_chmod,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
};

int main(int argc, char *argv[])
{
	//de_key = -en_key;
	//printf("%s\n", testing);
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}