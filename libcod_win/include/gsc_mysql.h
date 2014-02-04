#ifndef _GSC_MYSQL_H_
#define _GSC_MYSQL_H_

#define HIDDEN

/*HIDDEN*/ int gsc_mysql_init();
/*HIDDEN*/ int gsc_mysql_real_connect();
/*HIDDEN*/ int gsc_mysql_close();
/*HIDDEN*/ int gsc_mysql_query();
/*HIDDEN*/ int gsc_mysql_errno();
/*HIDDEN*/ int gsc_mysql_error();
/*HIDDEN*/ int gsc_mysql_affected_rows();
/*HIDDEN*/ int gsc_mysql_store_result();
/*HIDDEN*/ int gsc_mysql_num_rows();
/*HIDDEN*/ int gsc_mysql_num_fields();
/*HIDDEN*/ int gsc_mysql_field_seek();
/*HIDDEN*/ int gsc_mysql_fetch_field();
/*HIDDEN*/ int gsc_mysql_fetch_row();
/*HIDDEN*/ int gsc_mysql_free_result();
int gsc_mysql_real_escape_string();

/*HIDDEN*/ int gsc_mysql_stmt_init();
/*HIDDEN*/ int gsc_mysql_stmt_close();
/*HIDDEN*/ int gsc_mysql_stmt_get_stmt_id();
/*HIDDEN*/ int gsc_mysql_stmt_get_prefetch_rows();
/*HIDDEN*/ int gsc_mysql_stmt_get_param_count();
/*HIDDEN*/ int gsc_mysql_stmt_get_field_count();
/*HIDDEN*/ int gsc_mysql_stmt_prepare();
/*HIDDEN*/ int gsc_mysql_stmt_bind_param();
/*HIDDEN*/ int gsc_mysql_stmt_bind_result();
/*HIDDEN*/ int gsc_mysql_stmt_execute();
/*HIDDEN*/ int gsc_mysql_stmt_store_result();
/*HIDDEN*/ int gsc_mysql_stmt_fetch();

#endif
