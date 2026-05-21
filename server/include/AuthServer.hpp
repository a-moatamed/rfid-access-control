#pragma once

class AuthServer {
public:
    AuthServer();
    
    // TODO: Implement database lookup
    bool authorizeBadge(int badgeId) const;
};
