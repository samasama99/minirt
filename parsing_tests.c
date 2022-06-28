


// int main()
// {
//   assert(get_type(NULL).error);
//   assert(get_type("A").value == e_ambient);
//   assert(get_type("L").value == e_light);
//   assert(get_type("C").value == e_camera);
//   assert(get_type("sp").value == e_sphere);
//   assert(get_type("pl").value == e_plane);
//   assert(get_type("AB").error);

//   assert(get_digit(NULL).error);
//   assert(get_digit("1").value == 1);
//   assert(get_digit("5.1").error);

//   assert(get_ratio(NULL).error);
//   assert(is_equal_double(get_ratio("1.0").value, 1.0));
//   assert(get_ratio("5.1").error);
//   assert(is_equal_double(get_ratio("0.5").value, 0.5));

//   assert(get_color_ratio(NULL).error);
//   assert(get_color_ratio("256").error);
//   assert(get_color_ratio("10a").error);
//   assert(is_equal_double(get_color_ratio("200").value, 200 / 255.0));
//   assert(is_equal_double(get_color_ratio("60").value, 60 / 255.0));
//   assert(is_equal_double(get_color_ratio("0").value, 0 / 255.0));

//   assert(get_rgb(NULL).error);
//   assert(rgb_is_equal(color(1, 1, 1), get_rgb("255,255,255").value));
//   assert(get_rgb(",255,255,255").error);
//   assert(get_rgb("255,255,255,").error);
//   assert(rgb_is_equal(color(10/255., 15/255., 125/255.), get_rgb("10,15,125").value));

//   {
//     t_optional_material m = parse_ambient(get_array("A 0.2 255,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 0.8 50,0,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 1.0 50,0,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 0.0 50,0,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("X 0.2 255,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 0.2 ,255,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 1.5 255,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 0.5 300,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient(get_array("A 0.5 255,255,255,255", ' '));
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }

//   assert(get_int("1").value == 1);
//   assert(get_int("-1").value == -1);
//   assert(get_int("50").value == 50);
//   assert(get_int("-65645").value == -65645);
//   assert(get_int("-65645").error == false);
//   assert(get_int("-65645a").error == true);
//   assert(get_int(NULL).error == true);

//   if (get_double("1.1").error == false)
//     printf("1.1 %f\n", get_double("1.1").value);
//   else
//     printf("Error\n");
//   if (get_double("-1.1").error == false)
//     printf("-1.1 %f\n", get_double("-1.1").value);
//   else
//     printf("Error\n");
//   if (get_double("-50.0").error == false)
//     printf("-50.0 %f\n", get_double("-50.0").value);
//   else
//     printf("Error\n");
//   if (get_double("60").error == false)
//     printf("60 %f\n", get_double("60").value);
//   else
//     printf("Error\n");
//   if (get_double("0").error == false)
//     printf("0 %f\n", get_double("0").value);
//   else
//     printf("Error\n");
//   if (get_double("0a").error == false)
//     printf("0a %f\n", get_double("0a").value);
//   else
//     printf("Error\n");
//   if (get_double("a0").error == false)
//     printf("a0 %f\n", get_double("a0").value);
//   else
//     printf("Error\n");

//   print_tupil("test", get_position("-50.0,0,20").value);
//   print_tupil("test", get_position("-40.0,50.0,0.0").value);
//   assert(get_position("10,10,10,").error);
//   assert(get_position(",10,10,10").error);
//   assert(get_position("10,10,10,10").error);
//   t_optional_camera cam2 = parse_camera(get_array("C 0.0,1.5,-5 0,1,0 60", ' '), pair(600, 600));
//   assert(cam2.error == false);
//   t_camera ctest = camera(600, 600, M_PI / 3);
//   ctest.transform = view_transform(point(0, 1.5, -5),
//                                point(0, 1, 0),
//                                vector(0, 1, 0));
//   assert(ctest.half_height == cam2.value.half_height);
//   assert (ctest.half_width ==  cam2.value.half_width);
//   assert (ctest.hsize == cam2.value.hsize);
//   assert (ctest.pixel_size == cam2.value.pixel_size);
//   assert (ctest.transform.l1_c1 == cam2.value.transform.l1_c1);
//   assert (ctest.vsize == cam2.value.vsize);
//   t_optional_light l = parse_light(get_array("L -40.0,50.0,0.0 0.6 10,0,255", ' '));
//   assert(l.error == false);
//   print_tupil("light", l.value.position);
//   printf ("%f|", l.value.intensity.red);
//   printf ("%f|", l.value.intensity.green);
//   printf ("%f\n", l.value.intensity.blue);
//   system("leaks a.out");
// }
