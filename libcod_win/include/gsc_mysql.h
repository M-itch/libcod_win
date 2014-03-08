#ifndef _GSC_MYSQL_H_
#define _GSC_MYSQL_H_

void gsc_mysql_init();
void gsc_mysql_real_connect();
void gsc_mysql_close();
void gsc_mysql_query();
void gsc_mysql_errno();
void gsc_mysql_error();
void gsc_mysql_affected_rows();
void gsc_mysql_store_result();
void gsc_mysql_num_rows();
void gsc_mysql_num_fields();
void gsc_mysql_field_seek();
void gsc_mysql_fetch_field();
void gsc_mysql_fetch_row();
void gsc_mysql_free_result();
void gsc_mysql_real_escape_string();

int gsc_mysql_stmt_init();
int gsc_mysql_stmt_close();
int gsc_mysql_stmt_get_stmt_id();
int gsc_mysql_stmt_get_prefetch_rows();
int gsc_mysql_stmt_get_param_count();
int gsc_mysql_stmt_get_field_count();
int gsc_mysql_stmt_prepare();
int gsc_mysql_stmt_bind_param();
int gsc_mysql_stmt_bind_result();
int gsc_mysql_stmt_execute();
int gsc_mysql_stmt_store_result();
int gsc_mysql_stmt_fetch();

#endif
