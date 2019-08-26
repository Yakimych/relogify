CREATE TABLE communities (
    name character varying NOT NULL,
    description text,
    id integer NOT NULL
);

CREATE SEQUENCE communities_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE communities_id_seq OWNED BY communities.id;

CREATE TABLE players (
    id integer NOT NULL,
    name character varying NOT NULL,
    "communityId" integer NOT NULL
);

CREATE SEQUENCE players_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE players_id_seq OWNED BY players.id;

CREATE TABLE results (
    date timestamp with time zone NOT NULL,
    "player1Id" integer NOT NULL,
    "player2Id" integer NOT NULL,
    player1goals integer NOT NULL,
    player2goals integer NOT NULL,
    "communityId" integer NOT NULL,
    id integer NOT NULL,
    comment text,
    extratime boolean DEFAULT false NOT NULL
);

CREATE SEQUENCE results_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE results_id_seq OWNED BY results.id;

ALTER TABLE ONLY communities ALTER COLUMN id SET DEFAULT nextval('communities_id_seq'::regclass);

ALTER TABLE ONLY players ALTER COLUMN id SET DEFAULT nextval('players_id_seq'::regclass);

ALTER TABLE ONLY results ALTER COLUMN id SET DEFAULT nextval('results_id_seq'::regclass);

ALTER TABLE ONLY communities
    ADD CONSTRAINT communities_name_key UNIQUE (name);

ALTER TABLE ONLY communities
    ADD CONSTRAINT communities_pkey PRIMARY KEY (id);

ALTER TABLE ONLY players
    ADD CONSTRAINT "players_name_communityId_key" UNIQUE (name, "communityId");

ALTER TABLE ONLY players
    ADD CONSTRAINT players_pkey PRIMARY KEY (id);

ALTER TABLE ONLY results
    ADD CONSTRAINT results_pkey PRIMARY KEY (id);

ALTER TABLE ONLY players
    ADD CONSTRAINT "players_communityId_fkey" FOREIGN KEY ("communityId") REFERENCES communities(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY results
    ADD CONSTRAINT "results_communityId_fkey" FOREIGN KEY ("communityId") REFERENCES communities(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY results
    ADD CONSTRAINT "results_player1Id_fkey" FOREIGN KEY ("player1Id") REFERENCES players(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY results
    ADD CONSTRAINT "results_player2Id_fkey" FOREIGN KEY ("player2Id") REFERENCES players(id) ON UPDATE RESTRICT ON DELETE RESTRICT;
