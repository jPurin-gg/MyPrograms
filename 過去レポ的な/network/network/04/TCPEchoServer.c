#include <stdio.h>       /* printf()�Afprintf()�ɕK�v */
#include <stdlib.h>      /* atoi()�ɕK�v */
#include <string.h>      /* memset()�ɕK�v */

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>  /* socket()�Abind()�Aconnect()�ɕK�v */
#include <arpa/inet.h>   /* sockaddr_in�Ainet_ntoa()�ɕK�v */
#include <unistd.h>      /* close()�ɕK�v */
#endif /* _WIN32 */

#ifdef _WIN32
#define IS_INVALID_SOCKET(s) ((s) == INVALID_SOCKET)
#else
#define SOCKET int
#define IS_INVALID_SOCKET(s) ((s) < 0)
#define closesocket(s) close(s)
#endif /* _WIN32 */

#define MAXPENDING 5     /* �������̐ڑ��v���̍ő�l */
#define RCVBUFSIZE 32    /* ��M�o�b�t�@�̃T�C�Y */


void DieWithError(char *errorMessage);  /* �G���[�����֐� */
void HandleTCPClient(SOCKET clntSocket);   /* TCP�N���C�A���g�̏����֐� */
SOCKET CreateTCPServerSocket(unsigned short port); /* TCP�T�[�o�\�P�b�g���쐬 */
SOCKET AcceptTCPConnection(SOCKET servSock);  /* TCP�ڑ��v�����󂯕t���� */


int main(int argc, char *argv[])
{
    SOCKET servSock;                     /* �T�[�o�̃\�P�b�g�f�B�X�N���v�^ */
    SOCKET clntSock;                     /* �N���C�A���g�̃\�P�b�g�f�B�X�N���v�^ */
    unsigned short echoServPort;      /* �T�[�o�̃|�[�g�ԍ� */
#ifdef _WIN32
    WSADATA wsaData;
#else
    pid_t processID;                  /* fork()���Ԃ��v���Z�XID */
    unsigned int childProcCount = 0;  /* �q�v���Z�X�̐� */
#endif

#ifdef _WIN32
    WSAStartup(MAKEWORD(2,0), &wsaData);
#endif /* _WIN32 */


  if (argc != 2)    /* �����̐������������m�F */
  {
      fprintf(stderr, "Usage: %s <Server Port>", argv[0]);
      exit(EXIT_FAILURE);
  }

  echoServPort = atoi(argv[1]); /* 1�ڂ̈����F ���[�J���|�[�g */

  servSock = CreateTCPServerSocket(echoServPort);

  for (;;) /* �������J��Ԃ����s */
  {
      clntSock = AcceptTCPConnection(servSock);
#ifdef _WIN32 /* fork ���g�킸�A�����T�[�o�Ƃ��ē��� */
      HandleTCPClient(clntSock);
      closesocket(clntSock);
#else /* Linux �ł� fork ���g���ĕ��s�T�[�o�Ƃ��ē��� */
      /* �q�v���Z�X�̃t�H�[�N�ƃG���[��� */
    if ((processID = fork()) < 0) DieWithError("fork() failed");
    else if (processID == 0) /* �q�v���Z�X�̏ꍇ */
    {
         closesocket(servSock);   /* �҂��󂯒��̃\�P�b�g���q�v���Z�X���N���[�Y */
         HandleTCPClient(clntSock);

         exit(EXIT_SUCCESS);           /* �q�v���Z�X���I�� */
    }

    printf("with child process: %d\n", (int) processID);
    closesocket(clntSock);       /* �q�̃\�P�b�g�f�B�X�N���v�^��e���N���[�Y */
    childProcCount++;      /* ������̎q�v���Z�X�̐����C���N�������g */

    while (childProcCount) /* �S�]���r���N���[���A�b�v */
    {
        processID = waitpid((pid_t) -1, NULL, WNOHANG); /* �m���u���b�L���O�Ŏ��s */
        if (processID < 0) /* waitpid()�̃G���[���m�F */
            DieWithError("waitpid() failed");
        else if (processID == 0)  /* �]���r�����݂��Ȃ� */
            break;
        else
            childProcCount--;  /* �q�v���Z�X����� */
    }
#endif /* _WIN32 */
  }
  /* ���̕����ɂ͓��B���Ȃ� */
}


SOCKET CreateTCPServerSocket(unsigned short port)
{
    SOCKET sock;                        /* �쐬����\�P�b�g */
    struct sockaddr_in echoServAddr; /* ���[�J���A�h���X */

    /* ���M�ڑ��v���ɑ΂���\�P�b�g���쐬 */
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (IS_INVALID_SOCKET(sock))
        DieWithError("socket() failed");

    /* ���[�J���̃A�h���X�\���̂��쐬 */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    /* �\���̂��[���Ŗ��߂� */
    echoServAddr.sin_family = AF_INET;                /* �C���^�[�l�b�g�A�h���X�t�@�~�� */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* ���C���h�J�[�h���g�p */
    echoServAddr.sin_port = htons(port);              /* ���[�J���|�[�g */

    /* ���[�J���A�h���X�փo�C���h */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* ���M�ڑ��v���̃��X�����Ƃ����}�[�N���\�P�b�g�ɕt���� */
    if (listen(sock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    return sock;
}


SOCKET AcceptTCPConnection(SOCKET servSock)
{
    SOCKET clntSock;                   /* �N���C�A���g�̃\�P�b�g�f�B�X�N���v�^ */
    struct sockaddr_in echoClntAddr; /* �N���C�A���g�̃A�h���X */
    int clntLen;           /* �N���C�A���g�̃A�h���X�\���̂̒��� */

    /* ���o�̓p�����[�^�̃T�C�Y���Z�b�g */
    clntLen = sizeof(echoClntAddr);

    /* �N���C�A���g����̐ڑ��v����҂� */
    clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen);
    if (IS_INVALID_SOCKET(clntSock))
        DieWithError("accept() failed");

     /* clntSock�̓N���C�A���g�ɐڑ��ς� */

     printf ("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

     return clntSock;
}


void HandleTCPClient(SOCKET clntSocket)
{
  char echoBuffer[RCVBUFSIZE];  /* �G�R�[������̃o�b�t�@ */
  int recvMsgSize;  /* ��M���b�Z�[�W�̃T�C�Y */

  /* �N���C�A���g����̎�M���b�Z�[�W */
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  /* ��M����������𑗐M���A�]�����I�����Ă��Ȃ���Ύ�����M���� */
  while (recvMsgSize > 0) /* �[���͓]���̏I�����Ӗ����� */
  {
    /* ���b�Z�[�W���N���C�A���g�ɃG�R�[�o�b�N���� */
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");

    /* ��M����f�[�^���c���Ă��Ȃ����m�F���� */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("recv() failed");
  }

  closesocket(clntSocket);  /* �N���C�A���g�\�P�b�g���N���[�Y���� */
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(EXIT_FAILURE);
}
