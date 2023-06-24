#ifndef SERVER_HPP
#define SERVER_HPP

# include <sstream>
# include <iostream>
# include <iomanip>
# include <cstring>
# include <cstdlib>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <map>
# include <vector>
# include <poll.h>
# include <fcntl.h>
# include "User.hpp"
# include "Channel.hpp"
# include "ircGod.hpp"

class   Server
{
    protected :
        std::map<int, User*>                users;
        std::map<std::string, std::string>  gods;
        std::vector<pollfd>                 pollers;
        std::vector<Channel *>              servChannels;
        std::string                         passWord;
        std::string                         serverName;
        int                                 portNumber;
        int                                 numberOfCli;
        int                                 servSocketFd;
    public :
        Server();
        Server(int ac, char **av);
        Server(Server const &p);
        ~Server();
        Server  const &operator=(Server const &p);
    public :
        void    sendEveryOne(std::string buffer, User *currentUser);
        void    regularConnection(std::string buffer, User *UserX);
        void    createConnection();
        void    Authentication();
        void    nConnection();
        void    oConnection(int i);
        void    lostConnection(User *user);
        void	sendInstructions(int clientFd);
        void	sendWelcome(User *user);
        void    sendWelcome(User *user, Channel *current);
        void    handleOtherCmds(User *UserX, std::string* cmdParams, int paramNumber);
        void    sendReply(int clientFd, std::string prefix, std::string numericCode, std::string *params);
        bool	passCorrect(std::string passUser);
        bool	nickAlreadyInUse(std::string nick);
        bool	authenticated(int fdClient);
        void    defaultChannelsAdd(User *user);
        void    firstConnection(int i, char *buffer, User *UserX);
        /*-- COMMANDS PART 1--*/
        void    handleAuthentCmds(User *UserX, std::string* cmdParams, int paramNumber);
        void	handleCmdPass(std::string	*params, User *userX, int paramNumber);
        void	handleCmdNick(std::string	*params, User *userX, int paramNumber);
        void	handleCmdUser(std::string	*params, User *userX, int paramNumber);
        /*-- COMMANDS PART 2--*/
        void    handleCmdOper(std::string   *params, User *userX, int paramNumber);
        void    handleCmdMode(std::string   *params, User *userX, int paramNumber);
        void    handleCmdModeOpt(std::string *params, User *userX, Channel *chan);
        void    handleCmdModeOpt(Channel *chan, User *userX, std::map<char,std::string> opt, int mode);
        void    handleCmdModeOptI(User *userX, Channel *chan, int mode);
        void    handleCmdModeOptT(User *userX, Channel *chan, int mode);
        void    handleCmdModeOptO(User *userX, std::string s, Channel *chan, int mode);
        void    handleCmdModeOptK(User *userX, std::string s, Channel *chan, int mode);
        void    handleCmdModeOptL(User *userX, std::string s, Channel *chan, int mode); 
        /*-- COMMANDS PART 3--*/
        void    handleCmdJoin(std::string* str, User* Userx, int paramNumber);
        void    JoinFunc(std::map<std::string, std::string>   tmp, int i);
        void    handleCmdPart(std::string *s, User *userX, int paramNumber);
        void    ParsePart(std::string& channel, std::string& channel2, std::string* str, std::string& reason);
    
        /*-- HELPER-FUNCTIONS --*/
            int     findUserinChan(int fd, std::vector<User *> x);
            User    *findUserinServ(std::string name);
            void    deleteFromPoll(int fd);
        Channel     *channelFinder(std::string s);
        /*-------------------EXCEPTIONS------------------*/
        

        class errorNbArguments : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class errorPort : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class errorPass : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class errorErrno : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

};

#endif