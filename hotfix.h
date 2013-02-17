#ifndef _HOT_FIX_H_
#define _HOT_FIX_H_

struct patch_descriptor {
    void *orig_func;
    void *patch_func;
};

/* to be used in patch source file */
#define HOTFIX_BEGIN struct patch_descriptor hotfix_table[] = {
#define HOTFIX(orig_func, patch_func) {(orig_func), (patch_func)},
#define HOTFIX_END {NULL, NULL} };

/* to be called in the app*/
void hotfix_init(void);

#endif /*_HOT_FIX_H_*/
