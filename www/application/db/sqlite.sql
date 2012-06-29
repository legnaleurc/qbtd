create table 'groups' (
   'id' integer primary key,
   'name' varchar(20) not null,
   'description' varchar(100) not null
);
--INSERT INTO 'groups' VALUES (1,'admin','Administrator'),(2,'members','General User'),(3,'varified','email varified');
INSERT INTO 'groups' VALUES (1,'admin','Administrator');
INSERT INTO 'groups' VALUES (2,'members','General User');

CREATE TABLE 'users' (
   'id' integer primary key,
   'ip_address' integer unsigned NOT NULL,
   'username' varchar(100) NOT NULL,
   'password' varchar(40) NOT NULL,
   'salt' varchar(40) DEFAULT NULL,
   'email' varchar(100) NOT NULL,
   'activation_code' varchar(40) DEFAULT NULL,
   'forgotten_password_code' varchar(40) DEFAULT NULL,
   'forgotten_password_time' integer unsigned DEFAULT NULL,
   'remember_code' varchar(40) DEFAULT NULL,
   'created_on' integer unsigned NOT NULL,
   'last_login' integer unsigned DEFAULT NULL,
   'active' integer unsigned DEFAULT NULL,
   'first_name' varchar(50) DEFAULT NULL,
   'last_name' varchar(50) DEFAULT NULL,
   'company' varchar(100) DEFAULT NULL,
   'phone' varchar(20) DEFAULT NULL
);
INSERT INTO 'users' VALUES (1,2130706433,'admin','59beecdf7fc966e2f17fd8f65a4a9aeb09d4a3d4','9462e8eee0','admin@admin.com','',NULL,NULL,NULL,1268889823,1268889823,1,'Admin','istrator','ADMIN','0');

CREATE TABLE 'users_groups' (
   'id' integer primary key ,
   'user_id' integer unsigned NOT NULL,
   'group_id' integer unsigned NOT NULL
);
INSERT INTO 'users_groups' VALUES (1,1,1);
INSERT INTO 'users_groups' VALUES (2,1,2);

