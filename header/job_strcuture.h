struct TimeInfo {
};

struct ExecConstraints {
   void* dependent_jobs; 
};

struct Job {
    struct ExecConstraints ex_con;
    struct TimeInfo t_info;
};
