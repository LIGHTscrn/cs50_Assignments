SELECT COUNT(*) FROM movies JOIN ratings WHERE movies.id = ratings.movie_id AND rating = 10.0;
