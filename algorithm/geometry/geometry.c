#include "geometry.h"

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

        #ifdef debug
        __geometry_print_points(points, cnt_points);
        #endif
        
        __geometry_sort_points(&ch_ctx);

        __geometry_upper_cv(&ch_ctx);
        __geometry_lower_cv(&ch_ctx);

        __geometry_join_ul(&ch_ctx, &result);

        __geometry_cleanup_ch_ctx(&ch_ctx);
    }

    return result;
}

//algorithm: https://de.wikipedia.org/wiki/Bresenham-Algorithmus :D
void 
geometry_line(vec2_t *start, vec2_t *end, RASTER_FUNC_2D rFunc, void *data)
{   
    vec2_t  *s = start,
            *e = end;
    RASTER_FUNC_2D func = rFunc;
    void * dat = data;
    int32_t x0 = (int32_t)s->x,
             x1 = (int32_t)e->x,
             y0 = (int32_t)s->y,
             y1 = (int32_t)e->y;
    int32_t dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int32_t dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int32_t err = dx+dy, e2; /* error value e_xy */

    while (true) {
        func((int32_t const * const)&x0, (int32_t const * const)&y0, dat);//setPixel(x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void 
geometry_circle(vec2_t *center, int32_t *_radius, RASTER_FUNC_2D rFunc, void *data)
{
    int32_t radius = *_radius;
    vec2_t  *c = center;
    int32_t x0 = (int32_t)c->x,
            y0 = (int32_t)c->y;
    RASTER_FUNC_2D func = rFunc;
    void * dat = data;
    
    int32_t f = 1 - radius;
    int32_t ddF_x = 0;
    int32_t ddF_y = -2 * radius;
    int32_t x = 0;
    int32_t y = radius;

    int32_t tmp = y0 + radius;
    func((int32_t const * const)&x0, (int32_t const * const)&tmp, dat);
    tmp = y0 - radius;
    func((int32_t const * const)&x0, (int32_t const * const)&tmp, dat);
    tmp = x0 + radius;
    func((int32_t const * const)&tmp, (int32_t const * const)&y0, dat);
    tmp = x0 - radius;
    func((int32_t const * const)&tmp, (int32_t const * const)&y0, dat);

    while(x < y)
    {
        if(f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        int32_t tmps[8] = {
            /*0 x0px */ x0 + x,
            /*1 x0mx */ x0 - x,
            /*2 x0py */ x0 + y,
            /*3 x0my */ x0 - y,
            /*4 y0py */ y0 + y,
            /*5 y0my */ y0 - y,
            /*6 y0px */ y0 + x,
            /*7 y0mx */ y0 - x
        };

        func((int32_t const * const)&tmps[0], (int32_t const * const)&tmps[4], dat);
        func((int32_t const * const)&tmps[1], (int32_t const * const)&tmps[4], dat);
        func((int32_t const * const)&tmps[0], (int32_t const * const)&tmps[5], dat);
        func((int32_t const * const)&tmps[1], (int32_t const * const)&tmps[5], dat);
        func((int32_t const * const)&tmps[2], (int32_t const * const)&tmps[6], dat);
        func((int32_t const * const)&tmps[3], (int32_t const * const)&tmps[6], dat);
        func((int32_t const * const)&tmps[2], (int32_t const * const)&tmps[7], dat);
        func((int32_t const * const)&tmps[3], (int32_t const * const)&tmps[7], dat);
    }
}

void 
geometry_ellipse(vec2_t *center, int32_t *_a, int32_t *_b, RASTER_FUNC_2D rFunc, void *data)
{

    RASTER_FUNC_2D func = rFunc;
    void * dat = data;

    int32_t xm = (int32_t)center->x, 
            ym = (int32_t)center->y, 
            a = *_a, 
            b = *_b;

    int32_t dx = 0, dy = b; /* im I. Quadranten von links oben nach rechts unten */
    long a2 = a*a, b2 = b*b;
    long err = b2-(2*b-1)*a2, e2; /* Fehler im 1. Schritt */

    do {
        int32_t tmps[4] = { xm+dx, ym+dy, xm-dx, ym-dy };
        func((int32_t const * const)&tmps[0], (int32_t const * const)&tmps[1], dat); /* I. Quadrant */
        func((int32_t const * const)&tmps[2], (int32_t const * const)&tmps[1], dat); /* II. Quadrant */
        func((int32_t const * const)&tmps[2], (int32_t const * const)&tmps[3], dat); /* III. Quadrant */
        func((int32_t const * const)&tmps[0], (int32_t const * const)&tmps[3], dat); /* IV. Quadrant */

        e2 = 2*err;
        if (e2 <  (2*dx+1)*b2) { dx++; err += (2*dx+1)*b2; }
        if (e2 > -(2*dy-1)*a2) { dy--; err -= (2*dy-1)*a2; }
    } while (dy >= 0);

    int32_t tmp;
    while (dx++ < a) { /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
        tmp = xm+dx;
        func((int32_t const * const)&tmp, (int32_t const * const)&ym, dat); /* -> Spitze der Ellipse vollenden */
        tmp = xm-dx;
        func((int32_t const * const)&tmp, (int32_t const * const)&ym, dat);
    }
}

/* TRIANGULATION */

/* creats a list from pointer to vec, there is no need to allocate extra memory. */
static dl_list_t * __geometry_create_list_from_vecs(const vec3_t *vecs, size_t cnt_vecs) 
{
    dl_list_t * vec_list = dl_list_new();

    for ( size_t curVec = 0; curVec < cnt_vecs; ++curVec ) {
        dl_list_append(vec_list, (void*)&vecs[curVec]);
    }

    return vec_list;
}

//bool lines_intersect(vec2_t* _l1p1, vec2_t* _l1p2, vec2_t* _l2p1, vec2_t* _l2p2)
static bool __geometry_any_intersection(dl_list_t * vec_list, vec3_t *firstPt, vec3_t *lastPt,
                                                              int32_t *firstPtIdx, int32_t *lastPtIdx) {

    bool intersection = false;

    int32_t firstIdx = 0, lastIdx = 1, _firstPtIdx = *firstPtIdx, _lastPtIdx = *lastPtIdx;
    int32_t maxIdx = vec_list->cnt - 1;

    #ifdef debug
    printf("checking triangle index: %i - %i\n", _firstPtIdx, _lastPtIdx);
    #endif

    while ( firstIdx <= maxIdx ) {

        lastIdx = ( firstIdx == maxIdx ? 0 : firstIdx + 1 );

        #ifdef debug
        printf("checking intersection index: %i - %i\n", firstIdx, lastIdx);
        #endif

        if ( firstIdx < _firstPtIdx || firstIdx >= _lastPtIdx ) {

            vec3_t *f = (vec3_t*)dl_list_get(vec_list, firstIdx);
            vec3_t *l = (vec3_t*)dl_list_get(vec_list, lastIdx);

            vec2_t l1p1, l1p2, l2p1, l2p2, intersection_pt;
            l1p1.x = f->x;
            l1p1.y = f->y; 
            l1p2.x = l->x;
            l1p2.y = l->y; 

            l2p1.x = firstPt->x;
            l2p1.y = firstPt->y; 
            l2p2.x = lastPt->x;
            l2p2.y = lastPt->y;

            #ifdef debug
            printf("x: %.24f, y: %.24f\n",l1p1.x, l1p1.y);
            printf("x: %.24f, y: %.24f\n",l1p2.x, l1p2.y);
            printf("x: %.24f, y: %.24f\n",l2p1.x, l2p1.y);
            printf("x: %.24f, y: %.24f\n",l2p2.x, l2p2.y);
            #endif

            intersection = lineseg_intersect_pt(&intersection_pt, &l1p1, &l1p2, &l2p1, &l2p2);

            if ( intersection ) {
                
                bool neighbourCollision = (lastIdx == _firstPtIdx) || (firstIdx == _lastPtIdx);

                #ifdef debug
                //printf("intersection pt: including=%i\n", isStartPart);
                printf("x: %.24f, y: %.24f\n",intersection_pt.x, intersection_pt.y);
                #endif

                intersection &= !neighbourCollision;

                if ( intersection ) return true;

            }; 
        }
        
        ++firstIdx;
    }


    return false;
}

dl_list_t * 
geometry_triangulate(const vec3_t *vecs, size_t cnt_vecs) 
{
    dl_list_t * triangulated = NULL;

    if ( cnt_vecs > 3 ) {

        dl_list_t * vec_list = __geometry_create_list_from_vecs(vecs, cnt_vecs);
        
        triangulated = dl_list_new();

        int32_t maxIdx = cnt_vecs - 1;
        int32_t firstIdx = 0;
        int32_t lastIdx = 2;

        while ( maxIdx > 2) {

            int32_t middleIdx = lastIdx - 1;

            middleIdx = ( middleIdx < 0 ? (int32_t)vec_list->cnt - 1 : middleIdx );

            #ifdef debug
            printf("f: %i m: %i l: %i max: %i\n", firstIdx, middleIdx, lastIdx, maxIdx);
            #endif

            vec3_t *f,*m,*l;

            f = (vec3_t*)dl_list_get(vec_list, firstIdx);
            m = (vec3_t*)dl_list_get(vec_list, middleIdx);
            l = (vec3_t*)dl_list_get(vec_list, lastIdx);

            float place = place_of_vec3(f, l, m);
            
            #ifdef debug
            printf("\n ---- STEP ----\n\n");
            printf("%p = ", &*f);vec3_print(f);
            printf("%p = ", &*m);vec3_print(m);
            printf("%p = ", &*l);vec3_print(l);
            #endif

            /* we found convex point */
            if ( place < 0.f ) {

                /* but there is a chance for intersection. then we have to increase first and last index */
                if (__geometry_any_intersection(vec_list, f, l, &firstIdx, &lastIdx)) {
                    #ifdef debug
                    printf("Intersection!!!\n");
                    #endif
                    ++firstIdx; 
                    ++lastIdx; 
                } else {
                    #ifdef debug
                    printf("found triangle!!\n");
                    #endif
                    /* saving first triangle and removing middleIdx from pool, continue with lastIdx, and maxIdx - 1 */
                    dl_list_append(triangulated, &*f);
                    dl_list_append(triangulated, &*m);
                    dl_list_append(triangulated, &*l);

                    dl_list_remove(vec_list, middleIdx);

                    --maxIdx;
                }
                
            } else if ( place == 0.f ) {
                /* middleIdx is linear to others, we can remove it and retry with lastIdx, and maxIdx - 1 */
                #ifdef debug
                printf("linear, removing\n");
                #endif
                dl_list_remove(vec_list, middleIdx);
                
                --maxIdx;
            } else {
                #ifdef debug
                printf("not convex triangle!!\n");
                #endif
                /* there is no convex structure, we have to increase firstIdx and lastIdx and then continue*/
                ++firstIdx; 
                ++lastIdx; 
            }

            if ( maxIdx == 2 ) {
                #ifdef debug
                printf("last triangle!!\n");
                #endif
                /* here we are saving the last triangle */
                f = (vec3_t*)dl_list_get(vec_list, 0);
                m = (vec3_t*)dl_list_get(vec_list, 1);
                l = (vec3_t*)dl_list_get(vec_list, 2);
                
                dl_list_append(triangulated, &*f);
                dl_list_append(triangulated, &*m);
                dl_list_append(triangulated, &*l);

                break;
            }

            if ( lastIdx > maxIdx ) lastIdx = 0;
            if ( firstIdx > maxIdx ) firstIdx = 0;
            if ( firstIdx == maxIdx ) lastIdx = 1;
        }

        dl_list_clear(vec_list);
        dl_list_free(&vec_list);

    }

    return triangulated;
}

/* EOF TRIANGULATION */

/* START BEZIER */

void geometry_bezier1(vec2_t *start, vec2_t *cp, vec2_t *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data) 
{
    
    vec2_t middle;
    vec2_t middle_before;
    vec2_t middle_unit;
    vec2_t s_cp_unit;
    vec2_t s_cp;
    vec2_t cp_e_unit;
    vec2_t cp_e;
    vec2_t temp;

    float s_cp_len;
    float s_cp_step;
    float cp_e_len;
    float cp_e_step;
    float middle_len;
    float middle_step;
    float maxSteps = (float)*steps; 

    /* copy start values */
    vec2_copy_dest(&middle_before, start);
    vec2_copy_dest(&middle, start);

    /* compute needed values from start to ctrl point */
    vec2_copy_dest(&s_cp, start); // this seems to be unneeded
    vec2_sub_dest(&s_cp_unit, cp, start);
    s_cp_len = vec2_length(&s_cp_unit);
    s_cp_step = s_cp_len / maxSteps;

    vec2_normalize(&s_cp_unit);

    /* compute needed values from ctrl to start point */
    vec2_copy_dest(&cp_e, cp);  // this seems to be unneeded
    vec2_sub_dest(&cp_e_unit, end, cp);
    cp_e_len = vec2_length(&cp_e_unit);
    cp_e_step = cp_e_len / maxSteps;

    vec2_normalize(&cp_e_unit);

    for( float curStep = 1.0f; curStep <= maxSteps; ++curStep ) 
    {
        vec2_mul_dest(&temp, &s_cp_unit, curStep * s_cp_step);
        vec2_add_dest(&s_cp, start, &temp);

        vec2_mul_dest(&temp, &cp_e_unit, curStep * cp_e_step);
        vec2_add_dest(&cp_e, cp, &temp);

        vec2_sub_dest(&middle_unit, &cp_e, &s_cp);
        middle_len = vec2_length(&middle_unit);
        middle_step = middle_len / maxSteps;

        vec2_normalize(&middle_unit);

        vec2_mul_dest(&temp, &middle_unit, curStep * middle_step);
        vec2_add_dest(&middle, &s_cp, &temp);

        rFunc((vec2_t const * const)&middle_before, (vec2_t const * const)&middle, data);

        vec2_copy_dest(&middle_before, &middle);
    }


}

void geometry_bezier2(vec2_t *start, vec2_t *cp1, vec2_t *cp2, vec2_t *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data)
{
    vec2_t middle;
    vec2_t middle_before;
    vec2_t middle_unit;
    vec2_t s_cp1_unit;
    vec2_t s_cp1;
    vec2_t cp1_cp2_unit;
    vec2_t cp1_cp2;
    vec2_t cp2_e_unit;
    vec2_t cp2_e;
    vec2_t temp;

    float s_cp1_len;
    float s_cp1_step;
    float cp1_cp2_len;
    float cp1_cp2_step;
    float cp2_e_len;
    float cp2_e_step;
    float middle_len;
    float middle_step;
    float maxSteps = (float)*steps; 

    /* copy start values */
    vec2_copy_dest(&middle_before, start);
    vec2_copy_dest(&middle, start);

    /* compute needed values from start to ctrl point 1 */
    vec2_sub_dest(&s_cp1_unit, cp1, start);
    s_cp1_len = vec2_length(&s_cp1_unit);
    s_cp1_step = s_cp1_len / maxSteps;

    vec2_normalize(&s_cp1_unit);

    /* compute needed values from ctrl point 1 to ctrl point 2 */
    vec2_sub_dest(&cp1_cp2_unit, cp2, cp1);
    cp1_cp2_len = vec2_length(&cp1_cp2_unit);
    cp1_cp2_step = cp1_cp2_len / maxSteps;

    vec2_normalize(&cp1_cp2_unit);

    /* compute needed values from ctrl point 2 to end */
    vec2_sub_dest(&cp2_e_unit, end, cp2);
    cp2_e_len = vec2_length(&cp2_e_unit);
    cp2_e_step = cp2_e_len / maxSteps;

    vec2_normalize(&cp2_e_unit);

    for( float curStep = 1.0f; curStep <= maxSteps; ++curStep ) 
    {
        vec2_mul_dest(&temp, &s_cp1_unit, curStep * s_cp1_step);
        vec2_add_dest(&s_cp1, start, &temp);

        vec2_mul_dest(&temp, &cp1_cp2_unit, curStep * cp1_cp2_step);
        vec2_add_dest(&cp1_cp2, cp1, &temp);

        vec2_mul_dest(&temp, &cp2_e_unit, curStep * cp2_e_step);
        vec2_add_dest(&cp2_e, cp2, &temp);


        /* compute needed values from ctrl point 1 to ctrl point 2 */
        vec2_t side1;
        vec2_t side1_unit;
        float side1_len;
        float side1_step;

        vec2_sub_dest(&side1_unit, &cp1_cp2, &s_cp1);
        side1_len = vec2_length(&side1_unit);
        side1_step = side1_len / maxSteps;

        vec2_normalize(&side1_unit);

        vec2_mul_dest(&temp, &side1_unit, curStep * side1_step);
        vec2_add_dest(&side1, &s_cp1, &temp);

        /* compute needed values from ctrl point 1 to ctrl point 2 */
        vec2_t side2;
        vec2_t side2_unit;
        float side2_len;
        float side2_step;

        vec2_sub_dest(&side2_unit, &cp2_e, &cp1_cp2);
        side2_len = vec2_length(&side2_unit);
        side2_step = side2_len / maxSteps;

        vec2_normalize(&side2_unit);

        vec2_mul_dest(&temp, &side2_unit, curStep * side2_step);
        vec2_add_dest(&side2, &cp1_cp2, &temp);
        
        //---
        vec2_sub_dest(&middle_unit, &side2, &side1);
        middle_len = vec2_length(&middle_unit);
        middle_step = middle_len / maxSteps;

        vec2_normalize(&middle_unit);

        vec2_mul_dest(&temp, &middle_unit, curStep * middle_step);
        vec2_add_dest(&middle, &side1, &temp);

        rFunc((vec2_t const * const)&middle_before, (vec2_t const * const)&middle, data);

        vec2_copy_dest(&middle_before, &middle);
    }
}

/* EOF BEZIER */

