#include "geometry.h"
#include "dl_list.h"

#include <stdint.h>

typedef struct {
    size_t     cnt_points;
    vec2_t      **points;
    dl_list_t    *upper;
    dl_list_t    *lower;
} convex_hull_t;


typedef int (*__GEOM_CMP_FUNC)(const void*, const void*);

#ifdef debug
static void
__geometry_vec2_print_wrapper(vec2_t **vec) 
{
    printf("%p = ",*vec);vec2_print(*vec);
}

static void
__geometry_print_points(vec2_t *_points, size_t _cnt_points)
{
    vec2_t *points = _points;
    size_t cnt_points = _cnt_points;
    for(int i = 0; i < cnt_points; ++i)
    {
        printf("%p = ",&points[i]);vec2_print(&points[i]);
    }
}
#endif

static 
int __geometry_compare_points_ch(const vec2_t *_a, const vec2_t *_b) 
{
    const vec2_t *a = _a, *b = _b;
    int result = 0;
    if ( a->x > b->x ) 
    {
        result = 1;
    } else if (a->x < b->x ) 
    {
        result = -1;
    } else {
        if ( a->y > b->y ) 
        {
            result = -1;
        } else if (a->y < b->y)
        {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

static 
void __geometry_sort_points(convex_hull_t* ctx)
{

    #ifdef debug
        printf("points(%i): \n", ctx->cnt_points);
        __geometry_print_points(*ctx->points, ctx->cnt_points);
    #endif

    qsort(*ctx->points, ctx->cnt_points, sizeof(vec2_t), (__GEOM_CMP_FUNC)__geometry_compare_points_ch);

    #ifdef debug
        printf("points(sorted): \n");
        __geometry_print_points(*ctx->points, ctx->cnt_points);
    #endif
}

static float 
__geometry_curve_direction(vec2_t *start, vec2_t *end, vec2_t *point) 
{
    vec2_t *s = start, *e = end, *p = point;
    return (p->x - s->x) * (e->y - s->y) - (p->y - s->y) * (e->x - s->x);
}

static bool
__geometry_ch_should_delete(dl_list_t *list)
{   
    dl_list_t *u = list;
    return (    (u->cnt > 2 ) 
            &&  (__geometry_curve_direction(dl_list_get(u, (u->cnt-3))
                                           ,dl_list_get(u, (u->cnt-1))
                                           ,dl_list_get(u, (u->cnt-2))) >= 0.f));
}

static void 
__geometry_upper_cv(const convex_hull_t* ctx) 
{
    size_t cnt_points = ctx->cnt_points;
    dl_list_t *upper = ctx->upper;
    vec2_t *points = *ctx->points;

    uint32_t cur_upper_idx = 0;

    dl_list_append(upper, &points[cur_upper_idx]);
    dl_list_append(upper, &points[++cur_upper_idx]);

    for ( size_t cur_point = ++cur_upper_idx; cur_point < cnt_points; ++cur_point) {
        
        dl_list_append(upper, &points[cur_point]);

        while ( __geometry_ch_should_delete(upper) ) {
            dl_list_remove(upper, (upper->cnt-2));
        }
        
    }

    #ifdef debug
    printf("upper:\n");dl_list_each(upper, (EACH_FUNC)__geometry_vec2_print_wrapper);
    #endif

}

static void 
__geometry_lower_cv(const convex_hull_t* ctx) 
{

    size_t cnt_points = ctx->cnt_points;
    dl_list_t *lower = ctx->lower;
    vec2_t *points = *ctx->points;

    size_t cur_lower_idx = cnt_points-1;
    dl_list_append(lower, &points[cur_lower_idx]);
    dl_list_append(lower, &points[--cur_lower_idx]);

    for ( int32_t cur_point = --cur_lower_idx; cur_point > -1; --cur_point) {
        dl_list_append(lower, &points[cur_point]);
        while ( __geometry_ch_should_delete(lower) ) {
            dl_list_remove(lower, (lower->cnt-2));
        }
    }

    #ifdef debug
    printf("lower: \n");dl_list_each(lower, (EACH_FUNC)__geometry_vec2_print_wrapper);
    #endif
}

struct __gemoetry_join_ctx 
{
    int32_t index;
    vec2_t **array;
};

static void
__add_data_to_array(vec2_t **point, struct __gemoetry_join_ctx* _join_ctx) 
{
    struct __gemoetry_join_ctx *join_ctx = _join_ctx;
    #ifdef debug
        printf("index: %i ",join_ctx->index); __geometry_vec2_print_wrapper(point);   
    #endif
    join_ctx->array[join_ctx->index] = *point;
    ++join_ctx->index;
}

static void
 __geometry_join_ul(convex_hull_t* ctx, vec2_t ***_result)
{
    dl_list_t *upper = ctx->upper;
    dl_list_t *lower = ctx->lower;
    vec2_t **result;

    dl_list_remove(lower, (lower->cnt-1));
    dl_list_remove(lower, 0);

    #ifdef debug
    printf("lower truncated:\n");dl_list_each(lower, (EACH_FUNC)__geometry_vec2_print_wrapper);
    #endif

    size_t elements = (lower->cnt + upper->cnt + 1);
    result = calloc(elements, sizeof(vec2_t*));

    struct __gemoetry_join_ctx join_ctx = {0, result};

    dl_list_each_data(upper, &join_ctx, (EACH_FUNC_DATA) __add_data_to_array);
    dl_list_each_data(lower, &join_ctx, (EACH_FUNC_DATA) __add_data_to_array);

    *_result = result;
}

static void __geometry_cleanup_ch_ctx(convex_hull_t* ctx) {
    dl_list_free(&ctx->upper);
    dl_list_free(&ctx->lower);
}

vec2_t**
geometry_convex_hull(vec2_t *points, size_t cnt_points) 
{
    vec2_t **result = NULL;

    if (points && (cnt_points > 3)) {
        convex_hull_t ch_ctx = { cnt_points, &points, dl_list_new(), dl_list_new() };

        __geometry_print_points(points, cnt_points);

        __geometry_sort_points(&ch_ctx);

        __geometry_upper_cv(&ch_ctx);
        __geometry_lower_cv(&ch_ctx);

        __geometry_join_ul(&ch_ctx, &result);

        __geometry_cleanup_ch_ctx(&ch_ctx);
    }

    return result;
}
