#ifndef INT_BPT_WRAPPER
#define INT_BPT_WRAPPER

#ifdef __cpluscplus
extern "C" {
#endif
    typedef void* BPTHandle;
    BPTHandle bpt_create(int min_degree);
    void bpt_destory(BPTHandle tree);

    void bpt_insert(BPTHandle tree, int key);
    void bpt_search(BPTHandle tree, int key);
    void bpt_remove(BPTHandle tree, int key);

#ifdef __cplusplus
}
#endif

#endif
