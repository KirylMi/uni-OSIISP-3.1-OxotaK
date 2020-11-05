CREATE TABLE public.users
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 ),
    email text NOT NULL,
    username text NOT NULL,
    password text NOT NULL,
    privilege text NOT NULL,
    name text NOT NULL,
    active boolean NOT NULL DEFAULT false,
    PRIMARY KEY (id),
    UNIQUE (id), UNIQUE (email), UNIQUE (name), UNIQUE (username)
);
