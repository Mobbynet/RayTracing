//
// Created by grzes on 30.03.2023.
//

#include "hittable.h"

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool anything_hit = false;
    double closest_so_far = t_max;

    for(const auto& itr : objects){
        if(itr->hit(r,t_min,closest_so_far,temp_rec)){
            anything_hit = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return anything_hit;
}
