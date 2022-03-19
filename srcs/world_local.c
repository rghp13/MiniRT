#include "../includes/minirt.h"

t_ray	world_to_local(t_ray ray, t_vector3d pos, t_vector3d rot)
{
	ray.origin = transform_translate(ray.origin, -pos.x, -pos.y, -pos.z);
	ray.direction = transform_t_rotate(ray.direction, \
	get_all_axis_rotation(rot));
	ray.origin = transform_t_rotate(ray.origin, get_all_axis_rotation(rot));
	return (ray);
}

t_hit_result	local_to_world(t_hit_result hr, t_vector3d pos, t_vector3d rot)
{
	hr.inter_point = transform_inverse_rotate(hr.inter_point, \
	get_all_axis_rotation(rot));
	hr.normal = transform_inverse_rotate(hr.normal, get_all_axis_rotation(rot));
	hr.inter_point = transform_translate(hr.inter_point, pos.x, pos.y, pos.z);
	return (hr);
}
