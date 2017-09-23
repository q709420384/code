#ifndef C_VIEW_H
#define C_VIEW_H

void view_menu();
void reg_account(int sockfd);
int lading(int sockfd);
void view_afterlading(int sockfd);
void view_friends(int sockfd);
void* print_view_friend(int sockfd);
void sendfile_view(int sockfd);
void view_public(int sockfd);
void public_management_view(int sockfd);
void* print_view_public(int sockfd);
void view_members(int sockfd);
#endif
