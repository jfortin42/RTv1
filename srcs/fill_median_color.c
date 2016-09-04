#include "rtv1.h"

static float	**ft_malloc_free_tfloat(float **tab)
{
	int		i;

	i = -1;
	if (tab == NULL)
	{	
		if (!(tab = (float **)malloc(sizeof(float *) * 4)))
			return (NULL);
		while (++i < 4)
		{
			if (!(tab[i] = (float *)malloc(sizeof(float) * 3)))
				return (NULL);
		}
		return (tab);
	}
	else
	{
		while (++i < 4)
			free(tab[i]);
		free(tab);
		return (NULL);
	}
}

static float	*ft_get_color_pixel(t_mlx *mlx, int x, int y, float* tab)
{
	int		i;

	i = -1;
	while (++i < 3)
		tab[i] = (unsigned char)(mlx->d[(y * mlx->size_line) +
		 (x * (mlx->bpp / 8)) + i]) / 255.;
	return (tab);
}

static float	**ft_sort_color(float **tab, int size)
{
	float	tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (tab[j][i] > tab[j + 1][i])
			{
				tmp = tab[j][i];
				tab[j][i] = tab[j + 1][i];
				tab[j + 1][i] = tmp;
				j = -1;
			}
		}
	}
	return (tab);
}

static int		ft_fill_sort_color(int x,int y, t_mlx *mlx, float **tab)
{
	int		p;

			p = 0.0;
			if (x > 0 && ++p > 0)
				ft_get_color_pixel(mlx, x - 1, y, tab[p - 1]);
			if (x < WIN_W - 1 && ++p > 0)
				ft_get_color_pixel(mlx, x + 1, y, tab[p - 1]);
			if (y > 0 && ++p > 0)
				ft_get_color_pixel(mlx, x, y - 1, tab[p - 1]);
			if (y < WIN_H - 1 && ++p > 0)
				ft_get_color_pixel(mlx, x, y + 1, tab[p - 1]);
			ft_sort_color(tab, p);
			return (p);
}

void			ft_fill_median_color(t_mlx *mlx)
{
	float	r[3];
	float	**tab;
	int		p;
	int		x;
	int		y;

	if (!(tab = ft_malloc_free_tfloat(NULL)))
		return ;
	y = -1;
	while (++y < WIN_H)
	{
		x = (y % 2 == 0 ? 1 : 0);
		while (x < WIN_W)
		{
			ft_fzero(r, 3);
			p = ft_fill_sort_color(x, y, mlx, tab);
			if (p % 2 == 0)
				ft_average(r, tab[p - 2]);
			ft_average(r, tab[1]);
			p = (p % 2 == 0 ? 2 : 1);
		ft_put_pixel((t_th *)mlx, x, y, (((int)(r[2] / p * 255) & 0xff) << 16) +
		(((int)(r[1] / p * 255) & 0xff) << 8) + ((int)(r[0] / p * 255) & 0xff));
			x += 2;
		}
	}
	tab = ft_malloc_free_tfloat(tab);
}